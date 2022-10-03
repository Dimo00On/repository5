cmake_minimum_required(VERSION 3.20)
project(RegularSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(RegularSolver
        main.cpp
        basic_classes.cpp
        Builder.cpp
        Parser.cpp
        RepresenterNKA.cpp
        BuilderPDKA.cpp
        RepresenterPDKA.cpp
        Collector.cpp
        RegularExpression.cpp
        Minimizer.cpp GraphChecker.cpp GraphChecker.h)
