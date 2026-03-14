//
// Created by marci on 13.03.2026.
//

#include "Loader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Loader::Loader(const std::string& filename)
{
    readFromFile(filename);
}

void Loader::parseData(const std::string& line, unsigned int line_number)
{
    std::istringstream dataStream(line);

    if (line_number == 0)
        dataStream >> jobs_number >> machines_number >> init_seed >> upper_bound >> lower_bound;

    else
    {
        for (unsigned int i = 0; i < machines_number; i++)
        {
            float item;
            for (unsigned int j = 0; j < jobs_number; j++)
            {
                dataStream >> item;
                processing_times[i].push_back(item);
            }
        }
    }
}

bool Loader::readFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return false;
    }

    std::string line;
    unsigned int line_number = 0;
    while (std::getline(file, line))
    {
        parseData(line, line_number);
        line_number++;
    }

    file.close();
    return true;
}

unsigned int Loader::getJobsNumber() const
{
    return jobs_number;
}

unsigned int Loader::getMachinesNumber() const
{
    return machines_number;
}

unsigned int Loader::getInitSeed() const
{
    return init_seed;
}

unsigned int Loader::getUpperBound() const
{
    return upper_bound;
}

unsigned int Loader::getLowerBound() const
{
    return lower_bound;
}

float Loader::getProcessingTime(int job_number, int machine_number) const
{
    return processing_times[job_number][machine_number];
}
