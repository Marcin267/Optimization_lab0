
#ifndef OPTIMIZATION_LAB0_SIMULATEDANNEALING_H
#define OPTIMIZATION_LAB0_SIMULATEDANNEALING_H

#include "../Solution.h"
#include "../Problem.h"

class SimulatedAnnealing
{
    int max_steps = 0;
    float max_temperature = 0;
    float min_temperature = 0;
    float cooling_rate = 0;
    float best_fitness = 0;
    float current_fitness = 0;
    Solution current_solution;
    Solution best_solution;
    Problem* problem = nullptr;
    std::string result_file_name;
    std::vector<float> fitness_values;

public:
    explicit SimulatedAnnealing(Problem &problem_data, int max_steps, float max_temperature,
    float min_temperature, float cooling_rate, std::string result_file_name);
    float evaluate(const Solution& solution);
    void run();
    Solution createNeighbour();
    bool accept(float temperature, float fitness_diff);
    void saveResults();
};


#endif //OPTIMIZATION_LAB0_SIMULATEDANNEALING_H