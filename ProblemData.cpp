#include "ProblemData.h"
#include <iostream>
#include <fstream>
#include <sstream>

ProblemData::ProblemData(const std::string& filename)
{
    if(!loadFile(filename))
        std::cout << "Error opening file" << std::endl;
}

void ProblemData::parseLine(const std::string& line, unsigned int line_number)
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

bool ProblemData::loadFile(const std::string filename)
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

void ProblemData::display() const
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

unsigned int ProblemData::getJobsNumber() const {return jobs_number;}

unsigned int ProblemData::getMachinesNumber() const {return machines_number;}

unsigned int ProblemData::getInitSeed() const {return init_seed;}

unsigned int ProblemData::getUpperBound() const {return upper_bound;}

unsigned int ProblemData::getLowerBound() const {return lower_bound;}

float ProblemData::getProcessingTime(int job_number, int machine_number) const {return processing_times[job_number][machine_number];}
