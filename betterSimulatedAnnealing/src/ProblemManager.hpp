#ifndef PROBLEMMANAGER_HPP
#define PROBLEMMANAGER_HPP


#include "Solution.h"

#define PHI 0.50
#define MU 0.01
#define INTERNAL_ITERATIONS 10000
#define MAX_SUCCESES 200
#define MAX_NEIG 800

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

    void updateTemperature();

private:
    Solution *currentSolution;
    LowerTriangularMatrix<int> *distanceMatrix;
    Solution *bestSolutionEver;
    Solution *candidateSolution;
    int currentIteration;
    double originalTemperature;
    double temperature;
    int coolDownIteration;

    void coolDown();

    int neig_gen;
    int neig_success;
    int allTimeNeig;
    int last_delta;
    double last_exp;
    bool last_was_accepted;
};


#endif
