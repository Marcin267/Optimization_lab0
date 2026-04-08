#include "../include/Problem.h"
#include "../include/Solution.h"
#include <iostream>
#include <fstream>
#include <sstream>

Problem::Problem(const std::string& filename)
{
    if(!loadFile(filename))
    {
        std::cout << "Error opening file" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Problem::parseLine(const std::string& line, unsigned int line_number)
{
    std::istringstream dataStream(line);

    if (line_number == 0 || line_number == 2)
        return;

    if (line_number == 1)
    {
        dataStream >> jobs_number >> machines_number >> init_seed >> upper_bound >> lower_bound;
        processing_times.resize(machines_number);
    }

    else if (line_number >= 3)
    {
        for (unsigned int i = 0; i < jobs_number; i++)
        {
            float item;
            dataStream >> item;
            processing_times[line_number - 3].push_back(item);
        }
    }
}

bool Problem::loadFile(const std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string line;
    unsigned int line_number = 0;
    while (std::getline(file, line))
    {
        parseLine(line, line_number);
        line_number++;
    }

    file.close();
    return true;
}

void Problem::display() const
{
    std::cout << "number of jobs, number of machines, initial seed, upper bound and lower bound :" << std::endl;
    std::cout << jobs_number << " " << machines_number << " " << init_seed << " " << upper_bound << " " << lower_bound << std::endl;
    std::cout << "processing times:" << std::endl;
    for (unsigned int i = 0; i < machines_number; i++)
    {
        for (unsigned int j = 0; j < jobs_number; j++)
            std::cout << processing_times[i][j] << " ";
        std::cout << std::endl;
    }
}

float Problem::calculateC(std::vector<unsigned int> job_sequence) const
{
    std::vector<unsigned int> permutation = job_sequence;
    unsigned int permutation_count = permutation.size();
    unsigned int machines_count = getMachinesNumber();

    std::vector<std::vector<float>> C(permutation_count, std::vector<float>(machines_count, 0.0f));

    C[0][0] = getProcessingTime(permutation[0], 0);

    for (unsigned int i = 1; i < machines_count; i++)
        C[0][i] = C[0][i-1] + getProcessingTime(permutation[0], i);

    for (unsigned int i = 1; i < permutation_count; i++)
    {
        C[i][0] = C[i-1][0] + getProcessingTime(permutation[i], 0);

        for (unsigned int j = 1; j < machines_count; j++) {
            C[i][j] = std::max(C[i-1][j], C[i][j-1])
                     + getProcessingTime(permutation[i], j);
        }
    }

    return C[permutation_count-1][machines_count-1];
}

std::vector<float> Problem::evaluate(const std::vector<Solution> &solutions) const
{
    std::vector<float> results;
    unsigned int solutions_count = solutions.size();
    results.resize(solutions_count);
    for (unsigned int i = 0; i < solutions_count; i++)
        results[i] = calculateC(solutions[i].getJobSequence());
    return results;
}

unsigned int Problem::getJobsNumber() const {return jobs_number;}

unsigned int Problem::getMachinesNumber() const {return machines_number;}

unsigned int Problem::getInitSeed() const {return init_seed;}

unsigned int Problem::getUpperBound() const {return upper_bound;}

unsigned int Problem::getLowerBound() const {return lower_bound;}

float Problem::getProcessingTime(unsigned int job_index, unsigned int machine_index) const {return processing_times[machine_index][job_index];}
