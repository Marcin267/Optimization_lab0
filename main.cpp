#include <iostream>
#include "Problem.h"
#include <ctime>
#include <fstream>
#include "GeneticAlgorithm.h"
#include "RandomAlgorithm.h"
#include "GreedyAlgorithm.h"


int main()
{
    srand(time(nullptr));
    Problem problem("testData.txt");
    problem.display();
    GeneticAlgorithm genetic_algorithm(problem);
    genetic_algorithm.run("result_file.csv");
    RandomAlgorithm random_algorithm(problem, 10000);
    GreedyAlgorithm greedy_algorithm(problem);
}
