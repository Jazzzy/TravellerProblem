//
// Created by jazzzy on 11/18/16.
//

#include "ProblemManager.hpp"
#include "FileParser.h"
#include "TabuList.hpp"
#include <math.h>
#include "./DistanceMatrixWrapper.h"

extern int sizeOfProblem;
extern int maxNeig;
extern TabuList *tabuList;
LowerTriangularMatrix<int> *globDistanceMatrix;

ProblemManager::ProblemManager(char *pathOfDistances) {
    sizeOfProblem = getSizeOfProblem(pathOfDistances);
    maxNeig = (int) floor((sizeOfProblem - 1) * (sizeOfProblem - 2)) / 2;
    tabuList = new TabuList(sizeOfProblem - 1);
    this->stepsWithoutImprovements = 0;
    this->distanceMatrix = new LowerTriangularMatrix<int>((unsigned int) sizeOfProblem);
    fillMatrix(pathOfDistances, this->distanceMatrix);
    globDistanceMatrix = this->distanceMatrix;
    this->currentIteration = 0;
    this->reinitNumber = 0;
    initWrapper();
    this->currentSolution = new Solution();
    //this->currentSolution->setCost(calculateCostFor(this->currentSolution));
    this->bestSolutionEver = currentSolution;
}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    if (this->bestSolutionEver != this->currentSolution) {
        delete this->bestSolutionEver;
    }
    delete this->currentSolution;
    destroyWrapper();
}


Solution *ProblemManager::getNextSolution() {


    if (stepsWithoutImprovements >= STEPS_TO_RESET) {
        /*if (this->currentSolution != this->bestSolutionEver) {
            delete this->currentSolution;
        }
        this->currentSolution = bestSolutionEver;
        this->currentSolution->resetIte();*/

        delete this->currentSolution;

        /*IMPROV: We generate a new greedy solution*/
        this->currentSolution = new Solution();
        //this->currentSolution->setCost(calculateCostFor(this->currentSolution));


        tabuList->resetTabu();
        cout << endl << "***************\nREINICIO: " << ++this->reinitNumber << endl << "***************" << endl;
        stepsWithoutImprovements = 0;
    }

    Solution *bestSolutionYet = this->currentSolution->getNextNeighbour(this->distanceMatrix);

    Solution *nextSolution = this->currentSolution->getNextNeighbour(distanceMatrix);

    while (nextSolution != nullptr) {

        if (nextSolution->getCost() < bestSolutionYet->getCost()) {
            delete bestSolutionYet;
            bestSolutionYet = nextSolution;
        } else {

            delete nextSolution;
        }
        nextSolution = this->currentSolution->getNextNeighbour(distanceMatrix);
    }


    pair<int, int> p = bestSolutionYet->getGenePair();
    tabuList->addElement(p);





    if (this->bestSolutionEver->getCost() <= bestSolutionYet->getCost()) {
        this->stepsWithoutImprovements++;
    } else {
        this->bestSolutionEver = bestSolutionYet;
        stepsWithoutImprovements = 0;
    }
    if (this->currentSolution != this->bestSolutionEver)
        delete this->currentSolution;
    this->currentSolution = bestSolutionYet;
    this->currentSolution->setProblemIteration(currentIteration++);


    /*IMPROV: We add the pair to the frequency matrix*/
    //addFrec((unsigned int) p.first, (unsigned int) p.second);
    this->currentSolution->addFrequencyToMatrix();


    return this->currentSolution;
}


Solution *ProblemManager::getCurrentSolution() {
    return this->currentSolution;
}

void ProblemManager::printSolution(Solution *solution) {
    cout << endl << "ITERACION: " << solution->getProblemIteration() + 1 << endl;
    cout << "\tINTERCAMBIO: (" << solution->getGenePair().first << ", " << solution->getGenePair().second << ")" << endl
         << "\tRECORRIDO: ";
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
    cout << "\tITERACION: " << solution->getProblemIteration() + 1 << endl;
}

Solution *ProblemManager::getBestSolutionEver() {
    return this->bestSolutionEver;
}

int ProblemManager::calculateCostFor(Solution *solution) {
    int accumCost = 0;
    accumCost += distanceMatrix->getElement(0, (unsigned int) solution->getElemAt(0));
    for (int i = 0; i < (sizeOfProblem - 2); i++) {
        accumCost += distanceMatrix->getElement((unsigned int) solution->getElemAt(i),
                                                (unsigned int) solution->getElemAt(i + 1));
    }
    accumCost += distanceMatrix->getElement((unsigned int) solution->getElemAt(sizeOfProblem - 2), 0);
    return accumCost;

}


