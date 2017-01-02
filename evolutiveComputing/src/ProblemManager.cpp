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

    this->problemIteration = 0;
    this->currentPopulation = new Population(100);
    this->currentPopulation->generateFirstPopulation();
    this->currentPopulation->evaluateWholePopulation();

}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
}

bool ProblemManager::showMustGoOn() {
    return false;
}

void ProblemManager::printInitialPopulation() {
    currentPopulation->printFirstPopulation();
    cout << endl;
}

void ProblemManager::doAndPrint_SELECCION() {
    this->problemIteration++;

    cout << "ITERACION: " << this->problemIteration << ", SELECCION" << endl;
    this->newPopulation = new Population(100);

    for (int i = 0; i < REAL_POPULATION_SIZE - 2; i++) {
        cout << "\tTORNEO " << i << ": ";
        Solution *winner = this->currentPopulation->doTournament(rGen->getRandomPosition(), rGen->getRandomPosition());
        this->newPopulation->addIndividual(winner);
    }

}

void ProblemManager::doAndPrint_CROSS() {

}

void ProblemManager::doAndPrint_MUTATION() {

}

void ProblemManager::doAndPrint_REPLACEMENT() {

}





