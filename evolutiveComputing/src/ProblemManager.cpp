#include "ProblemManager.hpp"
#include "FileParser.h"
#include "PairList.hpp"
#include "RandomGanerator.h"

extern int sizeOfProblem;
extern int maxNeig;
LowerTriangularMatrix<int> *globDistanceMatrix;
PairList *pList;
extern RandomGanerator *rGen;


ProblemManager::ProblemManager(char *pathOfDistances) {
    sizeOfProblem = getSizeOfProblem(pathOfDistances);
    pList = new PairList(sizeOfProblem - 1);
    this->distanceMatrix = new LowerTriangularMatrix<int>((unsigned int) sizeOfProblem);
    fillMatrix(pathOfDistances, this->distanceMatrix);
    globDistanceMatrix = this->distanceMatrix;
    this->currentSolution = new Solution();
    this->bestSolutionEver = currentSolution;
}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    if (this->bestSolutionEver != this->currentSolution) {
        delete this->bestSolutionEver;
    }
    delete this->currentSolution;
}


Solution *ProblemManager::getNextSolution() {

    return nullptr;
}


Solution *ProblemManager::getCurrentSolution() {
    return this->currentSolution;
}


Solution *ProblemManager::getBestSolutionEver() {
    return this->bestSolutionEver;
}


bool ProblemManager::showMustGoOn() {
    return true;
}

void ProblemManager::printInitialSolution() {
    cout << endl;
}

void ProblemManager::printCurrentSolution() {
    cout << endl;
}

void ProblemManager::printLastSolution() {
    cout << endl;
}




