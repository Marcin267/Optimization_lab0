#ifndef OPTIMIZATION_LAB0_LOADER_H
#define OPTIMIZATION_LAB0_LOADER_H
#include "Solution.h"
#include <string>
#include <vector>


class Problem
{
    unsigned int jobs_number = 0;
    unsigned int machines_number = 0;
    unsigned int init_seed = 0;
    unsigned int upper_bound = 0;
    unsigned int lower_bound = 0;
    std::vector<std::vector<float>> processing_times;
    void parseLine(const std::string& line, unsigned int line_number);

public:
    explicit Problem(const std::string& filename);
    bool loadFile(std::string filename);
    float getProcessingTime(unsigned int job_index, unsigned int machine_index) const;
    void display() const;
    unsigned int getJobsNumber() const;
    unsigned int getMachinesNumber() const;
    unsigned int getInitSeed() const;
    unsigned int getUpperBound() const;
    unsigned int getLowerBound() const;
    std::vector<float> evaluate(const std::vector<Solution>& solutions) const;
    float calculateC(std::vector<unsigned int> job_sequence) const;
};


#endif //OPTIMIZATION_LAB0_LOADER_H