
#ifndef OPTIMIZATION_LAB0_SOLUTION_H
#define OPTIMIZATION_LAB0_SOLUTION_H
#include <vector>


class Solution
{
    unsigned int jobs_sequence_length = 0;
public:
    explicit Solution(unsigned int job_sequence_length);
    void fillJobSequence();
    std::vector <unsigned int> job_sequence;
    void mutate(float probability);
    unsigned int getJobNumber(unsigned int index);
    const std::vector<unsigned int> getJobSequence() const;
    Solution operator+(const Solution& father) const;
    void swap();
};



#endif //OPTIMIZATION_LAB0_SOLUTION_H