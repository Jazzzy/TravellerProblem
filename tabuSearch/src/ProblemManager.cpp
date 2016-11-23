//
// Created by jazzzy on 11/18/16.
//

#include "ProblemManager.hpp"
#include "FileParser.h"
#include "TabuList.hpp"
#include <math.h>

extern int sizeOfProblem;
extern int maxNeig;
extern TabuList *tabuList;

ProblemManager::ProblemManager(char *pathOfDistances) {

    sizeOfProblem = getSizeOfProblem(pathOfDistances);
    maxNeig = (int) floor((sizeOfProblem - 1) * (sizeOfProblem - 2)) / 2;
    tabuList = new TabuList(sizeOfProblem - 1);

    this->stepsWithoutImprovements = 0;
    this->distanceMatrix = new LowerTriangularMatrix<int>((unsigned int) sizeOfProblem);
    fillMatrix(pathOfDistances, this->distanceMatrix);

    this->currentSolution = new Solution();
    this->currentSolution->setCost(calculateCostFor(this->currentSolution));

    this->solutionNumber = 0;
    this->bestSolutionEver = currentSolution;
    this->currentIteration = 0;


}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    delete this->currentSolution;
}

#define STEPS_TO_RESET 100

Solution *ProblemManager::getNextSolution() {


    if (stepsWithoutImprovements >= STEPS_TO_RESET) {

        //reset;
    }

    cout << "Best Solution Ever Cost: " << bestSolutionEver->getCost() << endl;

    int cost1 = bestSolutionEver->getCost();

    Solution *bestSolutionYet = this->currentSolution->getNextNeighbour();
    if (bestSolutionEver->getCost() != cost1) cout << "HOW DIS THIS HAPPEN?_0: " << bestSolutionYet << ":" << bestSolutionEver << endl;
    if (bestSolutionYet != nullptr) {
        bestSolutionYet->setCost(calculateCostFor(bestSolutionYet));
    } else {
        perror("Impossible null pointer!");
        return nullptr;
    }

    Solution *nextSolution = this->currentSolution->getNextNeighbour();
    if (nextSolution != nullptr) {
        nextSolution->setCost(calculateCostFor(nextSolution));
    }

    while (nextSolution != nullptr) {

        if (nextSolution->getCost() < bestSolutionYet->getCost()) {
            delete bestSolutionYet;
            bestSolutionYet = nextSolution;
        } else {

            delete nextSolution;
        }

        nextSolution = this->currentSolution->getNextNeighbour();
        if (nextSolution != nullptr)
            nextSolution->setCost(calculateCostFor(nextSolution));

    }

    pair<int, int> p = bestSolutionYet->getGenePair();
    tabuList->addElement(p);

    delete this->currentSolution;
    this->currentSolution = bestSolutionYet;
    this->currentSolution->setProblemIteration(currentIteration++);

    if (this->bestSolutionEver->getCost() <= this->currentSolution->getCost()) {
        this->stepsWithoutImprovements++;
    } else {
        this->bestSolutionEver = this->currentSolution;
        stepsWithoutImprovements = 0;
    }


    return this->currentSolution;

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
    cout << endl << "ITERACION " << solution->getProblemIteration() + 1 << endl;
    this->neigNumber = 0;
    cout << "\tINTERCAMBIO: (" << solution->getGenePair().first << ", " << solution->getGenePair().second << ")" << endl << "\tRECORRIDO: ";
    solution->print();
    cout << "\tCOSTE (km): " << solution->getCost() << endl;
    cout << "\tITERACIONES SIN MEJORA: " << this->stepsWithoutImprovements << endl;
    cout << "\tLISTA TABU:";
    tabuList->printFormatted();
    cout << endl;

}

void ProblemManager::printSimpleSolution(Solution *solution) {
    cout << "\tRECORRIDO: ";
    solution->print();
    cout << "\tCOSTE (km): " << solution->getCost() << endl;
}

void ProblemManager::printSimpleSolutionWIte(Solution *solution) {
    cout << "\tRECORRIDO: ";
    solution->print();
    cout << "\tCOSTE (km): " << solution->getCost() << endl;
    cout << "\tITERACION: " << solution->getProblemIteration() << endl;
}

Solution *ProblemManager::getBestSolutionEver() {
    return this->bestSolutionEver;
}
