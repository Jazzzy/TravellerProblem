#include "ProblemManager.hpp"
#include "FileParser.h"
#include "PairList.hpp"
#include "RandomGanerator.h"

extern int sizeOfProblem;
extern int maxNeig;
LowerTriangularMatrix<int> *globDistanceMatrix;
PairList *pList;
extern RandomGanerator *rGen;

#define PHI 0.50
#define MU 0.01
#define INTERNAL_ITERATIONS 10000
#define MAX_SUCCESES 20
#define MAX_NEIG 80


ProblemManager::ProblemManager(char *pathOfDistances) {
    sizeOfProblem = getSizeOfProblem(pathOfDistances);
    pList = new PairList(sizeOfProblem - 1);
    this->distanceMatrix = new LowerTriangularMatrix<int>((unsigned int) sizeOfProblem);
    fillMatrix(pathOfDistances, this->distanceMatrix);
    globDistanceMatrix = this->distanceMatrix;
    this->currentSolution = new Solution(); //Greedy initialization
    this->currentSolution->setProblemIteration(0);
    this->bestSolutionEver = currentSolution;
    this->currentIteration = 0;


    this->originalTemperature = (MU / (-log(PHI))) * this->currentSolution->getCost();
    this->temperature = this->originalTemperature;
    this->coolDownIteration = 0;
    this->neig_gen = 0;
    this->neig_success = 0;
    this->allTimeNeig = 0;
    this->last_was_accepted = false;
}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    if (this->candidateSolution != this->bestSolutionEver && this->candidateSolution != this->currentSolution) {
        delete this->candidateSolution;
    }
    if (this->bestSolutionEver != this->currentSolution) {
        delete this->bestSolutionEver;
    }
    delete this->currentSolution;
}


Solution *ProblemManager::getNextSolution() {

    this->candidateSolution = nullptr;

    this->candidateSolution = this->currentSolution->getBestNeighbour(this->distanceMatrix); //take best
    if (this->candidateSolution == nullptr) {
        std::cerr
                << "We could not generete the best neighbour of the current solution, this kind of should never have happened :("
                << std::endl;
        exit(EXIT_FAILURE);
    }
    this->allTimeNeig++;
    this->neig_gen++;

    int delta = this->candidateSolution->getCost() - this->currentSolution->getCost();

    const double EulerConstant = std::exp(1.0);

    double exponential = pow(EulerConstant, ((-delta) / this->temperature));

    double randomValue = rGen->getRandomDouble();


    this->last_delta = delta;
    this->last_exp = exponential;

    if (delta < 0 || randomValue < exponential) {
        //We take the solution as the current one
        if (this->currentSolution != this->bestSolutionEver) {
            delete this->currentSolution;
        }
        this->currentSolution = this->candidateSolution;
        this->neig_success++;
        this->last_was_accepted = true;
    } else {
        this->last_was_accepted = false;
    }

    //We update out best solution ever on each iteration
    if (this->currentSolution->getCost() < this->bestSolutionEver->getCost()) {
        delete this->bestSolutionEver;
        this->bestSolutionEver = this->currentSolution;
    }


    this->candidateSolution->setProblemIteration(this->allTimeNeig);

    return this->candidateSolution;
}


Solution *ProblemManager::getCurrentSolution() {
    return this->currentSolution;
}


Solution *ProblemManager::getBestSolutionEver() {
    return this->bestSolutionEver;
}

void ProblemManager::coolDown() {
    this->temperature = this->originalTemperature / (1 + ++this->coolDownIteration);
    cout << "============================" << endl;
    cout << "ENFRIAMIENTO: " << this->coolDownIteration << endl;
    cout << "============================" << endl;
    cout << "TEMPERATURA: " << std::setprecision(6) << fixed << this->temperature << std::setprecision(6) << fixed
         << endl << endl;
}

void ProblemManager::updateTemperature() {
    if (neig_gen >= MAX_NEIG || neig_success >= MAX_SUCCESES) {
        this->neig_gen = 0;
        this->neig_success = 0;
        this->coolDown();
    }
    return;
}

bool ProblemManager::showMustGoOn() {
    return (this->allTimeNeig < INTERNAL_ITERATIONS);
}

void ProblemManager::printInitialSolution() {
    cout << "SOLUCIÓN INICIAL:" << endl;
    this->currentSolution->printSimple();
    cout << "\tTEMPERATURA INICIAL: " << std::setprecision(6) << fixed << this->originalTemperature << endl << endl;

}

void ProblemManager::printCurrentSolution() {
    cout << "ITERACION: " << this->allTimeNeig << endl;
    this->candidateSolution->print();
    cout << "\tDELTA: " << this->last_delta << endl;
    cout << "\tTEMPERATURA: " << this->temperature << endl;
    cout << "\tVALOR DE LA EXPONENCIAL: " << this->last_exp << endl;
    if (this->last_was_accepted) {
        cout << "\tSOLUCION CANDIDATA ACEPTADA" << endl;
    }
    cout << "\tCANDIDATAS PROBADAS: " << this->neig_gen << ", ACEPTADAS: " << this->neig_success << endl << endl;
}

void ProblemManager::printLastSolution() {

    cout << endl << "MEJOR SOLUCION: " << endl;
    this->bestSolutionEver->printSimpleWIte();
    cout << "\tmu = " << std::setprecision(2) << fixed << MU << ", phi = " << std::setprecision(1) << fixed << PHI
         << endl;


}




