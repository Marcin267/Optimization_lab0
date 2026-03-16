#ifndef OPTIMIZATION_LAB0_LOADER_H
#define OPTIMIZATION_LAB0_LOADER_H
#include <string>
#include <vector>


class ProblemData
{
    unsigned int jobs_number = 0;
    unsigned int machines_number = 0;
    unsigned int init_seed = 0;
    unsigned int upper_bound = 0;
    unsigned int lower_bound = 0;
    std::vector<std::vector<float>> processing_times;
    void parseLine(const std::string& line, unsigned int line_number);

public:
    explicit ProblemData(const std::string& filename);
    bool loadFile(const std::string filename);
    float getProcessingTime(int job_number, int machine_number) const;
    void display() const;
    unsigned int getJobsNumber() const;
    unsigned int getMachinesNumber() const;
    unsigned int getInitSeed() const;
    unsigned int getUpperBound() const;
    unsigned int getLowerBound() const;
};


#endif //OPTIMIZATION_LAB0_LOADER_H