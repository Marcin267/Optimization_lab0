
#ifndef OPTIMIZATION_LAB0_RANDOMALGORITHM_H
#define OPTIMIZATION_LAB0_RANDOMALGORITHM_H
#include "../Solution.h"
#include "../Problem.h"
#include <vector>


class RandomAlgorithm
{
    int best_index = 0;
    int worst_index = 0;
    int solutions_count;
    unsigned int job_sequence_length = 0;
    std::vector<Solution> solutions;
    std::vector<float> fitness_values;
    std::string result_file_name;
    const Problem* problem;
    void initialize();
    void evaluate();
    void saveResults() const;
    void run();
public:
    explicit RandomAlgorithm(const Problem& problem_data, int count, std::string file_name);
};


#endif //OPTIMIZATION_LAB0_RANDOMALGORITHM_H