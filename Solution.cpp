
#include "Solution.h"
#include <cstdlib>
#include <string>
#include <algorithm>

Solution::Solution(unsigned int jobs_number)
{
    jobs_sequence_length = jobs_number;
    job_sequence.resize(jobs_sequence_length);
}

void Solution::fillJobSequence()
{
    for (unsigned int i = 0; i < jobs_sequence_length; i++)
        job_sequence[i] = i;
    for (unsigned int i = 0; i < jobs_sequence_length; i++)
    {
        unsigned int random_index = rand() % jobs_sequence_length;
        unsigned int temp = job_sequence[i];
        job_sequence[i] = job_sequence[random_index];
        job_sequence[random_index] = temp;
    }
}

void Solution::mutate(float probability)
{
    if ((rand() % 100) < (probability * 100))
    {
        int first_index = rand() % jobs_sequence_length;
        int second_index = rand() % jobs_sequence_length;

        if (first_index == second_index)
        {
            while (first_index != second_index)
                second_index = rand() % jobs_sequence_length;
        }

        unsigned int temp = job_sequence[first_index];
        job_sequence[first_index] = job_sequence[second_index];
        job_sequence[second_index] = temp;
    }
}

Solution Solution::operator+(const Solution& father) const
{
    unsigned int start_index = rand() % jobs_sequence_length;
    unsigned int end_index = rand() % jobs_sequence_length;

    while (start_index == end_index)
        end_index = rand() % jobs_sequence_length;

    if (start_index > end_index)
        std::swap(start_index, end_index);

    Solution child(jobs_sequence_length);

    std::vector<unsigned int> mothers_gens;
    std::vector<unsigned int> fathers_gens(father.job_sequence);

    for (unsigned int i = start_index; i < end_index; i++)
    {
        mothers_gens.push_back(job_sequence[i]);
        fathers_gens.erase(
            std::remove(fathers_gens.begin(), fathers_gens.end(), job_sequence[i]),
            fathers_gens.end()
            );
    }

    unsigned int father_index = 0;

    for (unsigned int i = 0; i < jobs_sequence_length; i++)
    {
        if (i >= start_index && i < end_index)
            child.job_sequence[i] = mothers_gens[i - start_index];
        else
            child.job_sequence[i] = fathers_gens[father_index++];
    }

    return child;
}

unsigned int Solution::getJobNumber(unsigned int index) {return job_sequence[index];}

const std::vector<unsigned int> Solution::getJobSequence() const {return job_sequence;}
