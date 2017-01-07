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
    this->currentPopulation = new Population(REAL_POPULATION_SIZE);
    this->currentPopulation->generateFirstPopulation();
    this->currentPopulation->evaluateWholePopulation();
    this->reinicializationCounter = INIT_REINI_COUNTER;
    this->numberOfReinitalizations = 0;

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

    /**
     * Now we merge the two populations, sort them and keep the 100 best individuals
     * */
    this->newPopulation->mergePopulations(this->currentPopulation, REAL_POPULATION_SIZE);


    delete this->currentPopulation;
    this->currentPopulation = this->newPopulation;

    this->currentPopulation->printPopulation();

    cout << endl;

}

void ProblemManager::calcAndPrintBestIndividual() {
    cout << endl << "MEJOR SOLUCION: " << endl;
    cout << "RECORRIDO: ";

    this->currentPopulation->getIndividualAt(0)->printData();
    cout << endl << "FUNCION OBJETIVO (km): " << this->currentPopulation->getIndividualAt(0)->getCost() << endl;
    cout << "ITERACION: " << this->currentPopulation->getIndividualAt(0)->getProblemIteration() << endl;
}

void ProblemManager::doAndPrint_REINICIALIZATION() {

    bool allAreEqual = true;

    int sizeOfPopulation = this->currentPopulation->realSizeOfPopulation();

    int firstCost = this->currentPopulation->getIndividualAt(0)->getCost();

    for (int i = 0; i < sizeOfPopulation; i++) {
        Solution *currIndiv = this->currentPopulation->getIndividualAt(i);
        if (currIndiv->getCost() != firstCost) {
            allAreEqual = false;
        }
    }

    if (allAreEqual) {
        if (this->reinicializationCounter-- <= 0) {
            this->reinicializationCounter = INIT_REINI_COUNTER;
            this->reinitialize();
        }
    }
}


void ProblemManager::reinitialize() {

    cout << endl << "===============================" << endl << "REINICIALIZACION " << this->numberOfReinitalizations++
         << ": " << endl;


    Solution *bestSolutionYet = new Solution(this->currentPopulation->getIndividualAt(0), this->currentPopulation->getIndividualAt(0)->getProblemIteration());
    Solution *_2bestSolutionYet = new Solution(this->currentPopulation->getIndividualAt(1), this->currentPopulation->getIndividualAt(1)->getProblemIteration());

    delete this->currentPopulation;

    this->currentPopulation = new Population(REAL_POPULATION_SIZE);
    this->currentPopulation->generateRandomPopulationButTwo(bestSolutionYet,_2bestSolutionYet);
    this->currentPopulation->evaluateWholePopulation();
    this->currentPopulation->sortPopulation();

    cout << endl << "MEJOR SOLUCION: " << endl;
    cout << "RECORRIDO: ";

    this->currentPopulation->getIndividualAt(0)->printData();
    cout << endl << "FUNCION OBJETIVO (km): " << this->currentPopulation->getIndividualAt(0)->getCost() << endl;
    cout << "ITERACION: " << this->currentPopulation->getIndividualAt(0)->getProblemIteration() << endl;


    cout << "===============================" << endl << endl;

}





