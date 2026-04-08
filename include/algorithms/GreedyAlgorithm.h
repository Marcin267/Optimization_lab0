

#ifndef OPTIMIZATION_LAB0_GREEDYALGORITHM_H
#define OPTIMIZATION_LAB0_GREEDYALGORITHM_H
#include "../Problem.h"
#include <vector>
#include "../Solution.h"


class GreedyAlgorithm
{
    unsigned int job_number = 0;
    const Problem* problem = nullptr;
    std::vector<Solution> solutions;
    std::vector<float> fitness_values;
    std::string result_file_name;
public:
    explicit GreedyAlgorithm(const Problem& problem_data, std::string file_name);
    void generateSolutions();
    void run();
    void saveResults();
    unsigned int findNextJobNumber(const std::vector<unsigned int>& job_sequence, std::vector<unsigned int>& free_jobs);
    void evaluate();
};


#endif //OPTIMIZATION_LAB0_GREEDYALGORITHM_H