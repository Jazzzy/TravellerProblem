//
// Created by jazzzy on 11/18/16.
//

#ifndef TRAVELLERPROBLEM_FIRSTBEST_PROBLEMMANAGER_HPP
#define TRAVELLERPROBLEM_FIRSTBEST_PROBLEMMANAGER_HPP


#include "Solution.h"

class ProblemManager {
public:
    ProblemManager(char *pathOfDistances);

    virtual ~ProblemManager();

    Solution *getNextSolution();

    Solution *getCurrentSolution();

    Solution *getBestSolutionEver();

    void printSolution(Solution *solution);

    void printSimpleSolution(Solution *solution);

    void printSimpleSolutionWIte(Solution *solution);


private:
    int reinitNumber;
    int stepsWithoutImprovements;
    Solution *currentSolution;
    LowerTriangularMatrix<int> *distanceMatrix;
    int currentIteration;
    Solution *bestSolutionEver;

    int calculateCostFor(Solution *solution);

};


#endif //TRAVELLERPROBLEM_FIRSTBEST_PROBLEMMANAGER_HPP
