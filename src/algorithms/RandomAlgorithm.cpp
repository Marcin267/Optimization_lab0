
#include "../../include/algorithms/RandomAlgorithm.h"
#include <fstream>

RandomAlgorithm::RandomAlgorithm(const Problem& problem_data, const int count, std::string file_name)
{
    problem = &problem_data;
    job_sequence_length = problem->getJobsNumber();
    solutions_count = count;
    solutions.reserve(solutions_count);
    result_file_name = file_name;
    run();
}

void RandomAlgorithm::evaluate()
{
    fitness_values = problem -> evaluate(solutions);
    for (int i = 0; i < solutions_count; i++)
    {
        if (fitness_values[i] < fitness_values[best_index])
            best_index = i;
        else if (fitness_values[i] > fitness_values[worst_index])
            worst_index = i;
    }
}

void RandomAlgorithm::saveResults() const
{
    std::ofstream result_file;
    result_file.open(result_file_name, std::ios::app);
    result_file << "Best: " << fitness_values[best_index] << "["<< best_index << "]" << ";" <<"Worst index:" <<
        fitness_values[worst_index] << "["<< worst_index << "]" << std::endl;
    for (int i = 0; i < solutions_count; i++)
        result_file << i + 1 << ";" << fitness_values[i] << std::endl;
    result_file.close();
}

void RandomAlgorithm::initialize()
{
    for (int i = 0; i < solutions_count; i++)
    {
        Solution solution(job_sequence_length);
        solution.fillJobSequence();
        solutions.push_back(solution);
    }
}

void RandomAlgorithm::run()
{
    initialize();
    evaluate();
    saveResults();
}
