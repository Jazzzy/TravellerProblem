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

    bool showMustGoOn();

private:
    Solution *currentSolution;
    LowerTriangularMatrix<int> *distanceMatrix;
    Solution *bestSolutionEver;
    int currentIteration;
    double originalTemperature;
    double temperature;
    int coolDownIteration;
    void coolDown();
    void updateTemperature();

    int neig_gen;
    int neig_success;
    int allTimeNeig;
};


#endif
