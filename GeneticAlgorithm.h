#ifndef OPTIMIZATION_LAB0_GENETICALGORITHM_H
#define OPTIMIZATION_LAB0_GENETICALGORITHM_H

#include "Solution.h"
#include "Problem.h"
#include <vector>

class GeneticAlgorithm
{
    unsigned int population_size = 100; //Should be even!!!!! (fix it later)
    unsigned int generations = 80;
    float cross_probability = 0.4;
    float mutation_probability = 0.01;
    unsigned int tournament_size = 3;
    const Problem* problem = nullptr;
    std::vector<Solution> population;
    std::vector<Solution> new_generation;
    std::vector<float> fitness_values;

public:
    explicit GeneticAlgorithm(const Problem& problem_data);
    int tournamentSelect();
    std::pair<Solution, Solution> cross(Solution mother, Solution father);
    void createNewGeneration();
    void initialize();
    void run(const std::string& file_name);
    void evaluate();
    void saveResults(int generation, std::ofstream& results_file);
};


#endif //OPTIMIZATION_LAB0_GENETICALGORITHM_H