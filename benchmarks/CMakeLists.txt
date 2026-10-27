# Generate shared cases, compile isolated backends, then compare their CSV samples.
# This optional build uses only Python and SEL; Catch2 is not required.
find_package(Python3 3.6 REQUIRED COMPONENTS Interpreter)

if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64|i[3-6]86|x86)$")
    message(FATAL_ERROR "SEL benchmarks compare SSE4.1 backends and require an x86 target")
endif()
if(NOT MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(FATAL_ERROR "SEL benchmarks support MSVC, GCC, and Clang")
endif()

set(matrix_headers_dir "${PROJECT_SOURCE_DIR}/include/SEL/Maths/Matrices")
file(GLOB matrix_headers CONFIGURE_DEPENDS "${matrix_headers_dir}/Mat*x*.hpp")
# Track the header list as a generated dependency, including header removals.
set(matrix_shapes "${CMAKE_CURRENT_BINARY_DIR}/shapes.txt")
file(GENERATE OUTPUT "${matrix_shapes}" CONTENT "${matrix_headers}\n")
set(benchmark_source "${CMAKE_CURRENT_BINARY_DIR}/multiplication.cpp")
add_custom_command(
    OUTPUT "${benchmark_source}"
    COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/generate_benchmarks.py"
            --headers "${matrix_headers_dir}" --output "${benchmark_source}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/generate_benchmarks.py" "${matrix_shapes}" ${matrix_headers} "${PROJECT_SOURCE_DIR}/tests/Matrices/rectangular_products.json"
    COMMENT "Generating matrix multiplication benchmarks"
    VERBATIM
)
# One generation target is shared by both executables during parallel builds.
add_custom_target(sel_benchmark_cases DEPENDS "${benchmark_source}")

foreach(backend IN ITEMS scalar simd)
    add_executable(sel_bench_${backend} "${benchmark_source}" Escape.cpp)
    add_dependencies(sel_bench_${backend} sel_benchmark_cases)
    target_link_libraries(sel_bench_${backend} PRIVATE SEL::SEL)
    target_include_directories(sel_bench_${backend} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
    # The escape must remain opaque across translation units, even in an IPO build.
    set_target_properties(sel_bench_${backend} PROPERTIES INTERPROCEDURAL_OPTIMIZATION FALSE)
    if(MSVC)
        target_compile_options(sel_bench_${backend} PRIVATE /GL- /USEL_INTRINSIC_MATRIX_MUL)
    else()
        # Give both implementations the same instruction set and vectorization options.
        target_compile_options(sel_bench_${backend} PRIVATE -msse4.1 -fno-lto -USEL_INTRINSIC_MATRIX_MUL)
        target_link_options(sel_bench_${backend} PRIVATE -fno-lto)
    endif()
    # Set the switch in the generated source after command-line definitions are cleared.
    if(backend STREQUAL "simd")
        target_compile_definitions(sel_bench_${backend} PRIVATE SEL_BENCH_EXPLICIT_SIMD=1)
    else()
        target_compile_definitions(sel_bench_${backend} PRIVATE SEL_BENCH_EXPLICIT_SIMD=0)
    endif()
    target_compile_definitions(sel_bench_${backend} PRIVATE SEL_BENCH_CONFIG="$<CONFIG>")
endforeach()

# Capture flags per configuration without adding metadata to the library interface.
string(CONCAT benchmark_metadata
    "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}\n"
    "Configuration: $<CONFIG>\n"
    "Global flags: ${CMAKE_CXX_FLAGS}\n"
    "Configuration flags: "
    "$<$<CONFIG:Release>:${CMAKE_CXX_FLAGS_RELEASE}>"
    "$<$<CONFIG:RelWithDebInfo>:${CMAKE_CXX_FLAGS_RELWITHDEBINFO}>"
    "$<$<CONFIG:Debug>:${CMAKE_CXX_FLAGS_DEBUG}>\n"
    "Common benchmark options: $<JOIN:$<TARGET_PROPERTY:sel_bench_scalar,COMPILE_OPTIONS>, >\n"
    "Explicit SIMD: source-level off/on; auto-vectorization retained\n"
)
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/flags-$<CONFIG>.txt"
     CONTENT "${benchmark_metadata}")

# Generator expressions select the correct executables for multi-config builds.
add_custom_target(sel_bench_compare
    COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/compare.py"
            --scalar "$<TARGET_FILE:sel_bench_scalar>" --simd "$<TARGET_FILE:sel_bench_simd>"
            --metadata "${CMAKE_CURRENT_BINARY_DIR}/flags-$<CONFIG>.txt"
            --csv "${CMAKE_CURRENT_BINARY_DIR}/comparison-$<CONFIG>.csv"
    DEPENDS sel_bench_scalar sel_bench_simd
    USES_TERMINAL VERBATIM
)
