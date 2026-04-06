cmake_minimum_required(VERSION 4.1)
project(Optimization_lab0)

set(CMAKE_CXX_STANDARD 20)

add_executable(Optimization_lab0 main.cpp
        Problem.cpp
        Problem.h
        Solution.cpp
        Solution.h
        geneticAlgorithm.cpp
        geneticAlgorithm.h
        GreedyAlgorithm.cpp
        GreedyAlgorithm.h
        RandomAlgorithm.cpp
        RandomAlgorithm.h
)
