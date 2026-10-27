# Download a fixed Catch2 release into the build directory; no separate install needed.
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

find_package(Python3 3.6 REQUIRED COMPONENTS Interpreter)

# Reconfigure when shapes are added or removed, without reading implementations.
set(matrix_headers_dir "${PROJECT_SOURCE_DIR}/include/SEL/Maths/Matrices")
file(GLOB matrix_headers CONFIGURE_DEPENDS "${matrix_headers_dir}/Mat*x*.hpp")
# Track the list itself as well, so removing a header also regenerates fixtures.
set(matrix_shapes "${CMAKE_CURRENT_BINARY_DIR}/Matrices/shapes.txt")
file(GENERATE OUTPUT "${matrix_shapes}" CONTENT "${matrix_headers}\n")
set(matrix_generator "${CMAKE_CURRENT_SOURCE_DIR}/Matrices/generate_multiplication_tests.py")
set(matrix_tests "${CMAKE_CURRENT_BINARY_DIR}/Matrices/multiplication.cpp")
add_custom_command(
    OUTPUT "${matrix_tests}"
    COMMAND Python3::Interpreter "${matrix_generator}"
            --headers "${matrix_headers_dir}" --output "${matrix_tests}"
    DEPENDS "${matrix_generator}" "${matrix_shapes}" ${matrix_headers}
    COMMENT "Generating independently verified matrix multiplication tests"
    VERBATIM
)
# Both executables share one generation step, including during parallel builds.
add_custom_target(sel_matrix_fixtures DEPENDS "${matrix_tests}")

# Let CTest discover and run each Catch2 test case individually.
list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
include(Catch)

foreach(backend IN ITEMS scalar simd)
    add_executable(sel_tests_${backend} "${matrix_tests}" Matrices/Int4Tests.cpp)
    add_dependencies(sel_tests_${backend} sel_matrix_fixtures)
    target_include_directories(sel_tests_${backend} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Matrices")
    target_link_libraries(sel_tests_${backend} PRIVATE SEL::SEL Catch2::Catch2WithMain)

    if(backend STREQUAL "simd")
        target_compile_definitions(sel_tests_${backend} PRIVATE SEL_INTRINSIC_MATRIX_MUL)
        # The current integer intrinsics require SSE4.1. MSVC enables these
        # intrinsics directly; GCC and Clang require an explicit target flag.
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(sel_tests_${backend} PRIVATE -msse4.1)
        endif()
    else()
        # An externally supplied definition must not enable SIMD in this target.
        if(MSVC)
            target_compile_options(sel_tests_${backend} PRIVATE /USEL_INTRINSIC_MATRIX_MUL)
        else()
            target_compile_options(sel_tests_${backend} PRIVATE -USEL_INTRINSIC_MATRIX_MUL)
        endif()
    endif()

    catch_discover_tests(sel_tests_${backend}
        TEST_PREFIX "${backend}: " PROPERTIES LABELS "${backend}")
endforeach()
