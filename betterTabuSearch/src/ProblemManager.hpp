//
// Created by jazzzy on 11/18/16.
//

#ifndef TRAVELLERPROBLEM_FIRSTBEST_PROBLEMMANAGER_HPP
#define TRAVELLERPROBLEM_FIRSTBEST_PROBLEMMANAGER_HPP


#include "Solution.h"

#define STEPS_TO_RESET 100 //50

#define FREC_LIMIT 700 //(MU=0.005)500-3275(5007) 600-3210(6212) 800-3275(8209) 700-3210(7112)

/*
 * RESET: 100
 * LIMIT: 700
 * MU: 0.05
 * TABU: 200    3174 en 7414
 *
 * RESET: 100
 * LIMIT: 700
 * MU: 0.05
 * TABU: 1000    3181 en 8214 ite
 *
 * RESET: 100
 * LIMIT: 700
 * MU: 0.05
 * TABU: 500    3163 en 7311 ite
 *
 * */


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
