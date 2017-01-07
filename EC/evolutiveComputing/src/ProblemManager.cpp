#include "ProblemManager.hpp"
#include "FileParser.h"
#include "PairList.hpp"
#include "RandomGanerator.h"

extern int sizeOfProblem;
extern int maxNeig;
LowerTriangularMatrix<int> *globDistanceMatrix;
PairList *pList;
extern RandomGanerator *rGen;
extern unsigned int problemIteration;


ProblemManager::ProblemManager(char *pathOfDistances) {
    sizeOfProblem = getSizeOfProblem(pathOfDistances);
    pList = new PairList(sizeOfProblem - 1);
    this->distanceMatrix = new LowerTriangularMatrix<int>((unsigned int) sizeOfProblem);
    fillMatrix(pathOfDistances, this->distanceMatrix);
    globDistanceMatrix = this->distanceMatrix;

    problemIteration = 0;
    this->currentPopulation = new Population(100);
    this->currentPopulation->generateFirstPopulation();
    this->currentPopulation->evaluateWholePopulation();

}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    delete this->currentPopulation;
}

bool ProblemManager::showMustGoOn() {
    return problemIteration < MAX_ITERATIONS;
}

void ProblemManager::printInitialPopulation() {
    cout << "POBLACION INICIAL" << endl;
    currentPopulation->printPopulation();
    cout << endl;
}

void ProblemManager::doAndPrint_SELECCION() {
    problemIteration++;

    cout << "ITERACION: " << problemIteration << ", SELECCION" << endl;
    this->newPopulation = new Population(100);

    for (int i = 0; i < REAL_POPULATION_SIZE - 2; i++) {
        cout << "\tTORNEO " << i << ": ";
        Solution *winner = this->currentPopulation->doTournament(rGen->getRandomPosition(), rGen->getRandomPosition());
        this->newPopulation->addIndividual(winner);
    }
    cout << endl;
}

void ProblemManager::doAndPrint_CROSS() {
    cout << "ITERACION: " << problemIteration << ", CRUCE " << endl;

    for (int i = 0; i < REAL_POPULATION_SIZE - 2; i += 2) {
        double random = rGen->getRandomDouble();
        cout << "\tCRUCE: (" << i << ", " << i + 1 << ") (ALEATORIO: " << random << ")" << endl;
        this->newPopulation->doCross(i, i + 1, random);
    }
}

void ProblemManager::doAndPrint_MUTATION() {
    cout << "ITERACION: " << problemIteration << ", MUTACION" << endl;

    for (int i = 0; i < REAL_POPULATION_SIZE - 2; i++) {
        cout << "\tINDIVIDUO " << i << endl;
        this->newPopulation->doMutation(i);
        cout << endl;
    }
}

void ProblemManager::doAndPrint_REPLACEMENT() {

    cout << endl << "ITERACION: " << problemIteration << ", REEMPLAZO" << endl;

    this->newPopulation->evaluateWholePopulation();
    this->currentPopulation->sortPopulation();
    this->newPopulation->sortPopulation();


    for (int i = 0; i < ELITIST_NUMBER; i++) {
        this->newPopulation->addIndividualAtFront(new Solution(this->currentPopulation->getIndividualAt(i),
                                                               this->currentPopulation->getIndividualAt(
                                                                       i)->getProblemIteration()));
    }


    delete this->currentPopulation;
    this->currentPopulation = this->newPopulation;

    this->currentPopulation->printPopulation();

    cout << endl;

}

void ProblemManager::calcAndPrintBestIndividual() {
    cout << endl << "MEJOR SOLUCION: " << endl;
    cout << "RECORRIDO: ";

    this->currentPopulation->getIndividualAt(1)->printData();
    cout << endl << "FUNCION OBJETIVO (km): " << this->currentPopulation->getIndividualAt(1)->getCost() << endl;
    cout << "ITERACION: " << this->currentPopulation->getIndividualAt(1)->getProblemIteration() << endl;
}





