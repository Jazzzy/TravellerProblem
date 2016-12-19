#ifndef PROBLEMMANAGER_HPP
#define PROBLEMMANAGER_HPP


#include "Solution.h"



class ProblemManager {
public:
    ProblemManager(char *pathOfDistances);

    virtual ~ProblemManager();

    Solution *getNextSolution();

    Solution *getCurrentSolution();

    Solution *getBestSolutionEver();

    void printInitialSolution();

    void printCurrentSolution();

    void printLastSolution();

    bool showMustGoOn();

private:
    Solution *currentSolution;
    LowerTriangularMatrix<int> *distanceMatrix;
    Solution *bestSolutionEver;
    unsigned int problemIteration;
};


#endif