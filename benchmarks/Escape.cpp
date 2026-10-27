// Keep this translation unit separate and disable LTO for the benchmark targets.
// The caller must assume this function can observe outputs and modify inputs,
// preventing products from being eliminated or reused across timed batches.
namespace matrixBench
{
    // Intentionally empty: its unknown implementation at each call site is the
    // optimization barrier. Adding observable work would distort batch timings.
    void escape(void*, void*, void*) {}
}
