#ifndef PROBLEMMANAGER_HPP
#define PROBLEMMANAGER_HPP


#include "Solution.h"

#define PHI 0.80
#define MU 0.0006
#define INTERNAL_ITERATIONS 10000
#define MAX_SUCCESES 20
#define MAX_NEIG 50
#define ITE_LIMIT 100

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

    void reinit();

private:
    Solution *currentSolution;
    LowerTriangularMatrix<int> *distanceMatrix;
    Solution *bestSolutionEver;
    Solution *candidateSolution;
    int iterationsWithoutImprovements;
    double originalTemperature;
    double temperature;
    int coolDownIteration;
    int reinitIteration;

    void coolDown();

    int neig_gen;
    int neig_success;
    int allTimeNeig;
    int last_delta;
    double last_exp;
    bool last_was_accepted;
};


#endif
