#ifndef OPTIMIZATION_LAB0_GENETICALGORITHM_H
#define OPTIMIZATION_LAB0_GENETICALGORITHM_H

#include "../Solution.h"
#include "../Problem.h"
#include <vector>

class GeneticAlgorithm
{
    unsigned int population_size = 0; //Should be even (fix it later)
    unsigned int generations = 0;
    float cross_probability = 0;
    float mutation_probability = 0;
    unsigned int tournament_size = 0;
    const Problem* problem = nullptr;
    std::vector<Solution> population;
    std::vector<Solution> new_generation;
    std::vector<float> fitness_values;
    std::string result_file_name;

public:
    explicit GeneticAlgorithm(const Problem& problem_data, unsigned int pop_size, unsigned int generations_count,
    float cross_prob, float mutation_prob, unsigned int tour_size, std::string file_name);
    ~GeneticAlgorithm() = default;
    int tournamentSelect();
    std::pair<Solution, Solution> cross(Solution mother, Solution father);
    void createNewGeneration();
    void initialize();
    void run();
    void evaluate();
    void saveResults(int generation, std::ofstream& results_file);
};


#endif //OPTIMIZATION_LAB0_GENETICALGORITHM_H