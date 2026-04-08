
#include "../../include/algorithms/SimulatedAnnealing.h"
#include <cmath>
#include <fstream>

SimulatedAnnealing::SimulatedAnnealing(Problem &problem_data, int max_steps, float max_temperature,
    float min_temperature, float cooling_rate, std::string result_file_name)
    :   current_solution(problem_data.getJobsNumber()),
        best_solution(problem_data.getJobsNumber()),
        max_steps(max_steps), max_temperature(max_temperature), min_temperature(min_temperature),
        cooling_rate(cooling_rate), result_file_name(result_file_name)
{
    problem = &problem_data;
    current_solution.fillJobSequence();
    best_solution = current_solution;

    current_fitness = evaluate(current_solution);
    fitness_values.push_back(current_fitness);
    best_fitness = evaluate(best_solution);

    run();
}

Solution SimulatedAnnealing::createNeighbour()
{
    Solution neighbour = current_solution;
    neighbour.swap();
    return neighbour;
}

float SimulatedAnnealing::evaluate(const Solution& solution)
{
    return problem -> calculateC(solution.getJobSequence());
}

bool SimulatedAnnealing::accept(float temperature, float fitness_diff)
{
    if (fitness_diff < 0)
        return true;

    float acceptence_probability = exp(-fitness_diff / temperature);
    return ((rand() % 100) < (acceptence_probability * 100));
}

void SimulatedAnnealing::saveResults()
{
    std::ofstream result_file;
    result_file.open(result_file_name, std::ofstream::app);
    result_file << "Best_value " << best_fitness << std::endl;
    // for (float fitness_value : fitness_values)
    //     result_file << fitness_value << std::endl;

    result_file.close();
}

void SimulatedAnnealing::run()
{
    float current_temperature = max_temperature;

    while (current_temperature > min_temperature)
    {
        for (int i = 0; i < max_steps; i++)
        {
            Solution neighbour = createNeighbour();
            float neighbour_fitness = evaluate(neighbour);
            float fitness_diff = neighbour_fitness - current_fitness;

            if (accept(current_temperature, fitness_diff))
            {

                current_solution = neighbour;
                fitness_values.push_back(current_fitness);
                current_fitness = neighbour_fitness;

                if (current_fitness < best_fitness)
                {
                    best_solution = current_solution;
                    best_fitness = current_fitness;
                }
            }
        }
        current_temperature *= cooling_rate;
    }
    saveResults();
}
