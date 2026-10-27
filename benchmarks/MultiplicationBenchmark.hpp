#pragma once

// Benchmark lifecycle: prepare and validate inputs, warm up, calibrate, measure,
// then emit a sample. Only batched public operator* calls and escapes are timed.

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <cpuid.h>
#endif

#include <SEL/Maths/Matrix.hpp>
#include <SEL/Utilities/Timer.hpp>

namespace matrixBench
{
    void escape(void* left, void* right, void* products);

    // Each timed iteration processes this many independent matrix pairs.
    constexpr std::size_t batchSize = 64;
    constexpr double defaultSampleMs = 20;

    inline bool supportsSse41()
    {
#if defined(_MSC_VER)
        int registers[4];
        __cpuid(registers, 1);
        const bool sse41 = (registers[2] & (1 << 19)) != 0;
#else
        unsigned int eax, ebx, ecx, edx;
        const bool sse41 = __get_cpuid(1, &eax, &ebx, &ecx, &edx) && (ecx & bit_SSE4_1);
#endif
        return sse41;
    }

    // Reject unsuitable builds/CPUs before executing any benchmark cases.
    inline double settings(int argc, char** argv)
    {
        if (std::string(SEL_BENCH_CONFIG) != "Release")
        {
            throw std::runtime_error("Benchmarks require a Release build");
        }
        if (!supportsSse41())
        {
            throw std::runtime_error("Benchmarks require a CPU with SSE4.1 support");
        }
        double sampleMs = defaultSampleMs;
        if (argc != 1)
        {
            if (argc != 3 || std::string(argv[1]) != "--sample-ms")
            {
                throw std::runtime_error("Usage: sel_bench_{scalar,simd} [--sample-ms milliseconds]");
            }
            std::size_t parsed = 0;
            sampleMs = std::stod(argv[2], &parsed);
            if (parsed != std::string(argv[2]).size())
            {
                throw std::runtime_error("Invalid sample duration");
            }
        }
        if (!std::isfinite(sampleMs) || sampleMs <= 0 || sampleMs > 60000)
        {
            throw std::runtime_error("Sample duration must be in (0, 60000] ms");
        }
        std::cout << "shape,type,explicit_simd,ns_per_product,products,elapsed_ns,checksum\n";
        return sampleMs;
    }

    // Stable integer mixing produces varied bounded inputs without random-device
    // access. Binary fractions are exactly representable in both float types.
    template <class T>
    T inputValue(std::size_t index, std::size_t batch, unsigned int salt)
    {
        std::uint32_t bits = static_cast<std::uint32_t>(index + batch * 4099 + salt * 65537);
        bits = (bits ^ (bits >> 16)) * 0x7feb352du;
        bits = (bits ^ (bits >> 15)) * 0x846ca68bu;
        const int raw = int((bits ^ (bits >> 16)) % 5);
        if constexpr (std::is_same_v<T, sel::Int4>)
        {
            return T(int((bits ^ (bits >> 16)) % 16) - 8);
        }
        else if constexpr (std::is_unsigned_v<T>)
        {
            return static_cast<T>(raw);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            return static_cast<T>(raw - 2) / T(4);
        }
        else
        {
            return static_cast<T>(raw - 2);
        }
    }

    // Int4's conversion is explicit; preserve ordinary numeric conversions for
    // other types. Passing T also materializes mutable element proxies safely.
    template <class T>
    long double scalarValue(T value)
    {
        if constexpr (std::is_same_v<T, sel::Int4>)
        {
            return int(value);
        }
        else
        {
            return value;
        }
    }

    // Check every output against an independent row-by-column reference before
    // timing. Small inputs avoid 32-bit overflow; signed-byte outputs wrap below.
    template <class T, class Left, class Right, class Product, std::size_t Rows,
              std::size_t Inner, std::size_t Columns>
    void initializeAndValidate(std::vector<Left>& left, std::vector<Right>& right,
                               std::vector<Product>& products, const char* type)
    {
        for (std::size_t batch = 0; batch < batchSize; ++batch)
        {
            for (std::size_t row = 0; row < Rows; ++row)
            {
                for (std::size_t inner = 0; inner < Inner; ++inner)
                {
                    left[batch][row][inner] = inputValue<T>(row * Inner + inner, batch, 3);
                }
            }
            for (std::size_t inner = 0; inner < Inner; ++inner)
            {
                for (std::size_t column = 0; column < Columns; ++column)
                {
                    right[batch][inner][column] = inputValue<T>(inner * Columns + column, batch, 1);
                }
            }
            products[batch] = left[batch] * right[batch];
            for (std::size_t row = 0; row < Rows; ++row)
            {
                for (std::size_t column = 0; column < Columns; ++column)
                {
                    long double expected = 0;
                    long double scale = 0;
                    for (std::size_t k = 0; k < Inner; ++k)
                    {
                        const long double term = scalarValue<T>(left[batch][row][k])
                                               * scalarValue<T>(right[batch][k][column]);
                        expected += term;
                        scale += std::abs(term);
                    }
                    if constexpr (std::is_same_v<T, sel::Int4>)
                    {
                        // Mathematical normalization independent of SEL's Int4.
                        const int residue = (static_cast<int>(expected) % 16 + 16) % 16;
                        expected = residue >= 8 ? residue - 16 : residue;
                    }
                    else if constexpr (std::is_same_v<T, std::int8_t>)
                    {
                        const auto low = static_cast<unsigned int>(static_cast<int>(expected)) & 255u;
                        expected = low < 128u ? int(low) : int(low) - 256;
                    }
                    const long double actual = scalarValue<T>(products[batch][row][column]);
                    long double tolerance = 0;
                    if constexpr (std::is_floating_point_v<T>)
                    {
                        tolerance = 64 * std::numeric_limits<T>::epsilon() * std::max(1.0L, scale);
                    }
                    if (!std::isfinite(actual) || std::abs(actual - expected) > tolerance)
                    {
                        throw std::runtime_error(std::string("Incorrect product: ") + type + " "
                            + std::to_string(Rows) + "x" + std::to_string(Inner) + "x"
                            + std::to_string(Columns) + " batch=" + std::to_string(batch)
                            + " row=" + std::to_string(row) + " column=" + std::to_string(column));
                    }
                }
            }
        }
    }

    // Calibrate by doubling whole batches, keeping counts exact and guarding the
    // later multiplication by batchSize. A reported sample is measured separately
    // from calibration and retried if it falls below the requested duration.
    template <class Measure>
    std::size_t measureAtLeast(Measure& measure, std::size_t& batches, double targetNs)
    {
        std::size_t elapsed = measure(batches);
        while (static_cast<double>(elapsed) < targetNs)
        {
            if (batches > std::numeric_limits<std::size_t>::max() / (2 * batchSize))
            {
                throw std::runtime_error("Benchmark iteration count overflow");
            }
            batches *= 2;
            elapsed = measure(batches);
        }
        return elapsed;
    }

    // One invocation emits one timed CSV sample for a single shape/type. The
    // Python runner repeats whole executables and aggregates their samples.
    template <class T, class Left, class Right, std::size_t Rows,
              std::size_t Inner, std::size_t Columns>
    void run(const char* type, double sampleMs)
    {
        using Product = decltype(std::declval<Left>() * std::declval<Right>());
        std::vector<Left> left(batchSize);
        std::vector<Right> right(batchSize);
        std::vector<Product> products(batchSize);
        initializeAndValidate<T, Left, Right, Product, Rows, Inner, Columns>(
            left, right, products, type);

        auto measure = [&](std::size_t batches)
        {
            sel::Timer timer;
            for (std::size_t iteration = 0; iteration < batches; ++iteration)
            {
                // One opaque call per 64 products amortizes barrier overhead. All
                // outputs escape, and inputs may change before the next batch.
                escape(left.data(), right.data(), products.data());
                for (std::size_t batch = 0; batch < batchSize; ++batch)
                {
                    products[batch] = left[batch] * right[batch];
                }
            }
            escape(left.data(), right.data(), products.data());
            return timer.getNanoseconds();
        };
        measure(1); // Warm caches before calibration.
        std::size_t batches = 1;
        const double targetNs = sampleMs * 1e6;
        measureAtLeast(measure, batches, targetNs); // Discard calibration timing.
        const std::size_t elapsed = measureAtLeast(measure, batches, targetNs);

        // Reading all outputs also provides a cross-backend consistency check.
        // Checksum calculation and CSV output are excluded from timing.
        long double checksum = 0;
        for (const auto& product : products)
        {
            for (std::size_t row = 0; row < Rows; ++row)
            {
                for (std::size_t column = 0; column < Columns; ++column)
                {
                    checksum += scalarValue<T>(product[row][column]);
                }
            }
        }

        // Int4 uses explicit SIMD only for the selected same-size square products.
        constexpr bool explicitSimd = SEL_BENCH_EXPLICIT_SIMD
            && (std::is_same_v<T, std::int8_t> || std::is_same_v<T, int> || std::is_same_v<T, float>
                || (std::is_same_v<T, sel::Int4> && Rows == Inner && Inner == Columns
                    && (Rows == 4 || Rows == 8 || Rows == 16 || Rows == 32)));
        const std::size_t count = batches * batchSize;
        std::cout << Rows << 'x' << Inner << '*' << Inner << 'x' << Columns << ',' << type
                  << ',' << explicitSimd << ',' << std::setprecision(12)
                  << static_cast<double>(elapsed) / count << ',' << count << ',' << elapsed
                  << ',' << checksum << '\n';
    }
}
