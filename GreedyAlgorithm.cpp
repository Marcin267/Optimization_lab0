
#include "GreedyAlgorithm.h"

#include <algorithm>
#include <fstream>

GreedyAlgorithm::GreedyAlgorithm(const Problem& problem_data)
{
    problem = &problem_data;
    job_number = problem -> getJobsNumber();
    solutions.reserve(job_number);
    run();
}

unsigned int GreedyAlgorithm::findNextJobNumber(const std::vector<unsigned int>& job_sequence, std::vector<unsigned int>& free_jobs)
{
    std::vector<unsigned int> temp_job_sequence = job_sequence;
    unsigned int best_job_number = 0;
    temp_job_sequence.push_back(free_jobs[0]);
    float best_fitness = problem -> calculateC(temp_job_sequence);
    for (int i = 1; i < free_jobs.size(); i++)
    {
        temp_job_sequence.back() = free_jobs[i];
        float fitness = problem -> calculateC(temp_job_sequence);
        if (fitness < best_fitness)
        {
            best_fitness = fitness;
            best_job_number = i;
        }
    }
    return best_job_number;
}

void GreedyAlgorithm::generateSolutions()
{
    for (unsigned int i = 0; i < job_number; i++)
    {
        std::vector<unsigned int> job_sequence;
        std::vector<unsigned int> free_jobs;
        for (unsigned int j = 0; j < job_number; j++) {
            free_jobs.push_back(j);
        }

        free_jobs.erase(std::find(free_jobs.begin(), free_jobs.end(), i));
        job_sequence.push_back(i);

        while (!free_jobs.empty())
        {
            unsigned int best_index = findNextJobNumber(job_sequence, free_jobs);
            job_sequence.push_back(free_jobs[best_index]);
            free_jobs.erase(free_jobs.begin() + best_index);
        }
        Solution solution(job_number);
        solution.job_sequence = job_sequence;
        solutions.push_back(solution);
    }
}

void GreedyAlgorithm::evaluate()
{
    fitness_values = problem -> evaluate(solutions);
}

void GreedyAlgorithm::saveResults()
{
    const std::string file_name = "greedy_results.csv";
    std::ofstream result_file;
    result_file.open(file_name, std::ios::app);
    for (int i = 0; i < solutions.size(); i++)
        result_file << i + 1 << ";" << fitness_values[i] << std::endl;
    result_file.close();
}

void GreedyAlgorithm::run()
{
    generateSolutions();
    evaluate();
    saveResults();
}
