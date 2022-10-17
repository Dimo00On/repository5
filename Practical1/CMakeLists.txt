cmake_minimum_required(VERSION 3.16)
project(Practical1)

set(CMAKE_CXX_STANDARD 17)
#add_definitions(--coverage)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(GTest::GTest)
include_directories(GTest::Main)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(lib
        src/Interface.cpp
        )

add_executable(Practical1
        src/main.cpp
        )
add_dependencies(Practical1 lib)
target_link_libraries(Practical1 PUBLIC lib)

add_executable(tests
        tests/main_tests.cpp
        tests/sample_tests.cpp
        tests/error_tests.cpp
        tests/func_for_tests.cpp
        tests/normal_tests.cpp
        )
add_dependencies(tests lib)

target_link_libraries(tests PUBLIC GTest::GTest GTest::Main lib)
