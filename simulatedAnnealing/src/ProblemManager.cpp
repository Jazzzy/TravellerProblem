#include "ProblemManager.hpp"
#include "FileParser.h"

extern int sizeOfProblem;
extern int maxNeig;
LowerTriangularMatrix<int> *globDistanceMatrix;

ProblemManager::ProblemManager(char *pathOfDistances) {
    sizeOfProblem = getSizeOfProblem(pathOfDistances);
    this->distanceMatrix = new LowerTriangularMatrix<int>((unsigned int) sizeOfProblem);
    fillMatrix(pathOfDistances, this->distanceMatrix);
    globDistanceMatrix = this->distanceMatrix;
    this->currentSolution = new Solution(); //Greedy initialization
    this->bestSolutionEver = currentSolution;
    this->currentIteration = 0;
}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    if (this->bestSolutionEver != this->currentSolution) {
        delete this->bestSolutionEver;
    }
    delete this->currentSolution;
}


Solution *ProblemManager::getNextSolution() {
    //TODO
    return this->currentSolution;
}


Solution *ProblemManager::getCurrentSolution() {
    return this->currentSolution;
}


Solution *ProblemManager::getBestSolutionEver() {
    return this->bestSolutionEver;
}


