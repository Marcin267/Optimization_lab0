//
// Created by marci on 07.04.2026.
//

#ifndef OPTIMIZATION_LAB0_SIMULATION_H
#define OPTIMIZATION_LAB0_SIMULATION_H

#include <fstream>
#include "../json.hpp"
#include <vector>


class Simulation
{
public:
    using json = nlohmann::json;
    std::string config_file = "config.json";
    struct
    {
        unsigned int population_size = 0;
        unsigned int generations = 0;
        float mutation_probability = 0;
        float cross_probability = 0;
        unsigned int tournament_size = 0;
        int count;
        std::string result_file;
    }genetic_config;

    struct
    {
        int max_step = 0;
        float max_temperature = 0;
        float min_temperature = 0;
        float cooling_rate = 0;
        int count = 0;
        std::string result_file;
    }sa_config;

    int random_count = 0;
    std::string random_result_file;
    std::string greedy_result_file;
    std::vector <unsigned int> problem_files;

public:
    Simulation();
    void run(json config) const;
};


#endif //OPTIMIZATION_LAB0_SIMULATION_H