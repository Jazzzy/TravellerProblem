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

private:
    Solution *currentSolution;
    LowerTriangularMatrix<int> *distanceMatrix;
    int solutionNumber;
    int neigNumber;

    void printSolution(Solution *solution);
    void printNeig(Solution *solution);

    int calculateCostFor(Solution *solution);

    bool pickSolution_FIRSTBETTER(Solution *current, Solution *possible);

};


#endif //TRAVELLERPROBLEM_FIRSTBEST_PROBLEMMANAGER_HPP
