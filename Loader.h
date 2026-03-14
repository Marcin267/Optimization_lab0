//
// Created by marci on 13.03.2026.
//

#ifndef OPTIMIZATION_LAB0_LOADER_H
#define OPTIMIZATION_LAB0_LOADER_H
#include <string>
#include <vector>


class Loader
{
    unsigned int jobs_number = 0;
    unsigned int machines_number = 0;
    unsigned int init_seed = 0;
    unsigned int upper_bound = 0;
    unsigned int lower_bound = 0;
    std::vector<std::vector<float>> processing_times;
    void parseData(const std::string& line, unsigned int line_number);

    public:
    explicit Loader(const std::string& filename);
        bool readFromFile(const std::string& filename);
        unsigned int getJobsNumber() const;
        unsigned int getMachinesNumber() const;
        float getProcessingTime(int job_number, int machine_number) const;
        unsigned int getInitSeed() const;
        unsigned int getUpperBound() const;
        unsigned int getLowerBound() const;
};


#endif //OPTIMIZATION_LAB0_LOADER_H