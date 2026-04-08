cmake_minimum_required(VERSION 4.1)
project(Optimization_lab0)

set(CMAKE_CXX_STANDARD 20)

add_executable(Optimization_lab0 main.cpp
        src/Problem.cpp
        include/Problem.h
        src/Solution.cpp
        include/Solution.h
        src/algorithms/GeneticAlgorithm.cpp
        include/algorithms/GeneticAlgorithm.h
        src/algorithms/GreedyAlgorithm.cpp
        include/algorithms/GreedyAlgorithm.h
        src/algorithms/RandomAlgorithm.cpp
        include/algorithms/RandomAlgorithm.h
        src/algorithms/SimulatedAnnealing.cpp
        include/algorithms/SimulatedAnnealing.h
        src/Simulation.cpp
        include/Simulation.h
)
