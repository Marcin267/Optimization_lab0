#include <iostream>
#include "ProblemData.h"
#include <ctime>


int main()
{
    ProblemData* problem = new ProblemData("testData.txt");
    problem->display();
    srand(time(nullptr));
}
