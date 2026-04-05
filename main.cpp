#include <iostream>
#include "Problem.h"
#include <ctime>
#include <fstream>
#include "GeneticAlgorithm.h"


int main()
{
    srand(time(nullptr));
    Problem problem("testData.txt");
    problem.display();
    GeneticAlgorithm algorithm(problem);
    algorithm.run("result_file.csv");
}
