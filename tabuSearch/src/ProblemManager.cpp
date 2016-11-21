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

    printSolution(currentSolution);

}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    delete this->currentSolution;
}

bool ProblemManager::pickSolution_FIRSTBETTER(Solution *current, Solution *possible) {
    return ((possible == nullptr) || (current->getCost() > possible->getCost()));
}

#define STEPS_TO_RESET 100

Solution *ProblemManager::getNextSolution() {


    if (stepsWithoutImprovements >= STEPS_TO_RESET) {

        //reset;
    }


    Solution *bestSolutionYet = this->currentSolution->getNextNeighbour();
    if (bestSolutionYet != nullptr)
        bestSolutionYet->setCost(calculateCostFor(bestSolutionYet));


    Solution *nextSolution = this->currentSolution->getNextNeighbour();
    if (nextSolution != nullptr)
        nextSolution->setCost(calculateCostFor(nextSolution));


    while (nextSolution != nullptr) {
        //TODO FREE MEMORY
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


    if (this->bestSolutionEver->getCost() <= bestSolutionYet->getCost()) {
        this->stepsWithoutImprovements++;
    } else {
        bestSolutionEver = bestSolutionYet;
        stepsWithoutImprovements = 0;
    }

    pair<int, int> p = bestSolutionYet->getGenePair();
    tabuList->addElement(p);


    delete this->currentSolution;
    this->currentSolution = bestSolutionYet;
    printSolution(currentSolution);
    return this->currentSolution;

    /*Solution *nextSolution = this->currentSolution->getNextNeighbour();
    nextSolution->setCost(calculateCostFor(nextSolution));
    printNeig(nextSolution);

    while (!pickSolution_FIRSTBETTER(this->currentSolution, nextSolution)) {
        delete nextSolution;
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

    }*/

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
    cout << endl << " " << solution->getCost() << "km" << endl;
    cout << "changing  (" << solution->getGenePair().first << "," << solution->getGenePair().second << ")" << endl << endl;
}

void ProblemManager::printNeig(Solution *solution) {
    pair<int, int> p = solution->getGenePair();
    cout << "\tVECINO V_" << neigNumber++ << " -> Intercambio: (" << p.first << ", " << p.second << "); ";
    solution->print();
    cout << " " << solution->getCost() << "km" << endl;
}
