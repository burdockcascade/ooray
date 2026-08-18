cmake_minimum_required(VERSION 3.25)
project(ooray LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option to toggle building unit tests (default ON)
option(OORAY_BUILD_TESTS "Build unit tests" ON)

# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------

include(FetchContent)

# 1. Fetch Raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# 2. Header-only library for ooray
add_library(ooray INTERFACE)
target_include_directories(ooray INTERFACE include)
target_link_libraries(ooray INTERFACE raylib)

# -----------------------------------------------------------------------------
# Target: Unit Tests
# -----------------------------------------------------------------------------
if(OORAY_BUILD_TESTS)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.5.2
    )
    set(CATCH_BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set(CATCH_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(CATCH_BUILD_EXTRA_TESTS OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(Catch2)

    set(TEST_SOURCES
            tests/test_vector2.cpp
            tests/test_vector3.cpp
            tests/test_vector4.cpp
            tests/test_rectangle.cpp
    )

    add_executable(unit-tests ${TEST_SOURCES})

    target_link_libraries(unit-tests PRIVATE
            ooray
            raylib
            Catch2::Catch2WithMain
    )

endif()