cmake_minimum_required(VERSION 3.20)
project(RegularSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(RegularSolver
        main.cpp
        basic_classes.h
        basic_classes.cpp
        Builder.cpp
        Builder.h
        Parser.cpp
        Parser.h
        RepresenterNKA.cpp
        RepresenterNKA.h
        BuilderPDKA.cpp
        BuilderPDKA.h
        RepresenterPDKA.cpp
        RepresenterPDKA.h
        Collector.cpp
        Collector.h
        RegularExpression.cpp
        RegularExpression.h
        Cleaner.cpp
        Cleaner.h
        Minimizer.cpp
        Minimizer.h)
