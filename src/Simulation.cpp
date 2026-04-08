
#include "../include/Simulation.h"
#include <iostream>
#include "../include/Problem.h"
#include <ctime>
#include <fstream>
#include "../json.hpp"
#include "../include/algorithms/GeneticAlgorithm.h"
#include "../include/algorithms/RandomAlgorithm.h"
#include "../include/algorithms/GreedyAlgorithm.h"
#include "../include/algorithms/SimulatedAnnealing.h"

Simulation::Simulation()
{
    std::ifstream file(config_file);
    json config;
    file >> config;
    file.close();

    genetic_config.population_size = config["population_size"];
    genetic_config.generations = config["generations"];
    genetic_config.mutation_probability = config["mutation_prob"];
    genetic_config.cross_probability = config["cross_prob"];
    genetic_config.tournament_size = config["tournament_size"];
    genetic_config.count = config["algorithm_counts"]["genetic"];
    genetic_config.result_file = config["result_files"]["genetic"];

    sa_config.max_step = config["max_step"];
    sa_config.max_temperature = config["max_temperature"];
    sa_config.min_temperature = config["min_temperature"];
    sa_config.cooling_rate = config["cooling_rate"];
    sa_config.count = config["algorithm_counts"]["simulated_annealing"];
    sa_config.result_file = config["result_files"]["simulated_annealing"];

    random_count = config["algorithm_counts"]["random"];
    random_result_file = config["result_files"]["random"];

    greedy_result_file = config["result_files"]["greedy"];

    run(config);
}

void Simulation::run(nlohmann::json config) const
{

    srand(time(nullptr));

    for (const auto& problem_file : config["problem_files"])
    {
        std::string results_path = "results/";
        std::string file_name = "instances/" + problem_file.get<std::string>();
        Problem problem(file_name);

        for (int i = 0; i < genetic_config.count; i++)
            GeneticAlgorithm genetic_algorithm(problem, genetic_config.population_size , genetic_config.generations,
                genetic_config.cross_probability, genetic_config.mutation_probability,
                genetic_config.tournament_size,results_path + genetic_config.result_file);

        for (int i = 0; i < sa_config.count; i++)
            SimulatedAnnealing simulated_annealing(problem, sa_config.max_step, sa_config.max_temperature,
                sa_config.min_temperature, sa_config.cooling_rate, results_path + sa_config.result_file);

        RandomAlgorithm random_algorithm(problem, random_count, results_path + random_result_file);
        GreedyAlgorithm greedy_algorithm(problem, results_path + greedy_result_file);
    }
};

