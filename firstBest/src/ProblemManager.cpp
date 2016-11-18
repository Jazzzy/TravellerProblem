//
// Created by jazzzy on 11/18/16.
//

#include "ProblemManager.hpp"
#include "DistanceFileParser.h"
#include <math.h>

extern int sizeOfProblem;
extern int maxNeig;


ProblemManager::ProblemManager(char *pathOfDistances) {

    sizeOfProblem = getSizeOfProblem(pathOfDistances);
    maxNeig = (int) floor((sizeOfProblem - 1) * (sizeOfProblem - 2)) / 2;
    this->distanceMatrix = new LowerTriangularMatrix<int>((unsigned int) sizeOfProblem);
    fillMatrix(pathOfDistances, this->distanceMatrix);
    this->currentSolution = new Solution();
    this->currentSolution->setCost(calculateCostFor(this->currentSolution));
    this->solutionNumber = 0;

    printSolution(currentSolution);

}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    //TODO: Probably
    delete this->currentSolution;
}

bool ProblemManager::pickSolution_FIRSTBETTER(Solution *current, Solution *possible) {
    return ((possible == nullptr) || (current->getCost() > possible->getCost()));
}

Solution *ProblemManager::getNextSolution() {
    Solution *nextSolution = this->currentSolution->getNextNeighbour();
    nextSolution->setCost(calculateCostFor(nextSolution));
    printNeig(nextSolution);

    while (!pickSolution_FIRSTBETTER(this->currentSolution, nextSolution)) {
        nextSolution = this->currentSolution->getNextNeighbour();
        if (nextSolution == nullptr) break;
        nextSolution->setCost(calculateCostFor(nextSolution));

        printNeig(nextSolution);
    }

    if (nextSolution == nullptr) {              //We have reached the final solution for this problem.

        return nullptr;                     //The current solution is the final one.

    } else {                                  //We have a better solution than the current one.

        delete this->currentSolution;
        this->currentSolution = nextSolution;
        printSolution(currentSolution);
        return this->currentSolution;

    }

}


int ProblemManager::calculateCostFor(Solution *solution) {

    int accumCost = 0;
    accumCost += this->distanceMatrix->getElement(0, (unsigned int) solution->getElemAt(0));
    for (int i = 0; i < (sizeOfProblem - 2); i++) {
        accumCost += this->distanceMatrix->getElement((unsigned int) solution->getElemAt(i), (unsigned int) solution->getElemAt(i + 1));
    }
    accumCost += this->distanceMatrix->getElement((unsigned int) solution->getElemAt(sizeOfProblem - 2), 0);
    return accumCost;

}

Solution *ProblemManager::getCurrentSolution() {
    return this->currentSolution;
}

void ProblemManager::printSolution(Solution *solution) {
    cout << endl << "SOLUCION S_" << solutionNumber++ << " -> ";
    this->neigNumber = 0;
    solution->print();
    cout << " " << solution->getCost() << "km" << endl;
}

void ProblemManager::printNeig(Solution *solution) {
    pair<int, int> p = solution->getGenePair();
    cout << "\tVECINO V_" << neigNumber++ << " -> Intercambio: (" << p.first << ", " << p.second <<"); " ;
    solution->print();
    cout << " " << solution->getCost() << "km" << endl;
}
