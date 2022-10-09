cmake_minimum_required(VERSION 3.16)
project(RegularSolver)

enable_testing()
find_package(GTest REQUIRED)
include_directories(GTest::GTest)
include_directories(GTest::Main)

set(CMAKE_CXX_STANDARD 17)

file(MAKE_DIRECTORY bin)
file(MAKE_DIRECTORY lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(lib
        src/basic_classes.cpp
        src/Builder.cpp
        src/Parser.cpp
        src/RepresenterNKA.cpp
        src/BuilderPDKA.cpp
        src/RepresenterPDKA.cpp
        src/Collector.cpp
        src/RegularExpression.cpp
        src/Minimizer.cpp
        src/GraphChecker.cpp
        src/Interface.cpp
        )

add_executable(RegularSolver
        main.cpp
        )
add_dependencies(RegularSolver lib)
target_link_libraries(RegularSolver PUBLIC lib)

add_executable(tests
        test/main_tests.cpp
        test/test_complement.cpp
        test/test_equality.cpp test/test_complex.cpp)
add_dependencies(tests lib)

target_link_libraries(tests PUBLIC GTest::GTest GTest::Main lib)
