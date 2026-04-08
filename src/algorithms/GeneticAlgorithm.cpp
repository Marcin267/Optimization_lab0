#include "../../include/algorithms/GeneticAlgorithm.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <utility>

GeneticAlgorithm::GeneticAlgorithm(const Problem& problem_data, unsigned int pop_size, unsigned int generations_count,
    float cross_prob, float mutation_prob, unsigned int tour_size, std::string file_name)
    :   population_size(pop_size), generations(generations_count), cross_probability(cross_prob),
        mutation_probability(mutation_prob),tournament_size(tour_size), result_file_name(file_name)
{
    problem = &problem_data;

    population.reserve(population_size);
    new_generation.reserve(population_size);
    fitness_values.reserve(population_size);
    run();
}

int GeneticAlgorithm::tournamentSelect()
{
    int best_index = rand() % population_size;

    for (int i = 0; i < tournament_size; i++)
    {
        int current_index = rand() % population_size;
        if (fitness_values[best_index] > fitness_values[current_index])
            best_index = current_index;
    }

    return best_index;
}

std::pair<Solution, Solution> GeneticAlgorithm::cross(Solution mother, Solution father)
{
    if ((rand() % 100) < (cross_probability * 100))
    {
        Solution first_child = mother + father;
        Solution second_child = father + mother;

        first_child.mutate(mutation_probability);
        second_child.mutate(mutation_probability);

        return {first_child, second_child};
    }
    mother.mutate(mutation_probability);
    father.mutate(mutation_probability);

    return {mother, father};
}

void GeneticAlgorithm::createNewGeneration()
{
    for (int i = 0; i < population_size / 2; i++)
    {
        int mother_index = tournamentSelect();
        int father_index = tournamentSelect();
        std::pair<Solution, Solution> children = cross(population[mother_index], population[father_index]);

        new_generation.push_back(children.first);
        new_generation.push_back(children.second);
    }
    population = new_generation;
    new_generation.clear();
    new_generation.reserve(population_size);
}

void GeneticAlgorithm::evaluate()
{
    fitness_values = problem->evaluate(population);
}

void GeneticAlgorithm::initialize()
{
    unsigned int jobs_number = problem->getJobsNumber();

    for (unsigned int i = 0; i < population_size; i++)
    {
        Solution solution(jobs_number);
        solution.fillJobSequence();
        population.push_back(solution);
    }
}

void GeneticAlgorithm::saveResults(int generation, std::ofstream& results_file)
{
    int generation_number = generation;
    auto [min_iterator, max_iterator] = std::minmax_element(fitness_values.begin(), fitness_values.end());
    float best = *min_iterator;
    float worst = *max_iterator;
    float avg = (std::accumulate(fitness_values.begin(), fitness_values.end(), 0.0f)) / fitness_values.size();

    results_file << generation_number << ";" << best << ";" << avg << ";" << worst << std::endl;
}

void GeneticAlgorithm::run()
{
    initialize();

    std::ofstream result_file;
    result_file.open(result_file_name, std::ios::app);

    for (int generation = 1; generation <= generations; generation++)
    {
        evaluate();
        saveResults(generation, result_file);
        createNewGeneration();
    }
    result_file.close();
}
