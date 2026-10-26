cmake_minimum_required(VERSION 3.21)
project(SEL LANGUAGES CXX)

# SEL is header-only: this target shares include paths and compiler requirements.
add_library(SEL INTERFACE)
add_library(SEL::SEL ALIAS SEL)
target_include_directories(SEL INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(SEL INTERFACE cxx_std_17)

# Enable tests only when building SEL directly, not from another project.
if(PROJECT_IS_TOP_LEVEL)
    # CTest comes with CMake and provides the BUILD_TESTING option (ON by default).
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()
