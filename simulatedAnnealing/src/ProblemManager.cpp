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
    this->bestSolutionEver = currentSolution;
    this->currentIteration = 0;


    this->originalTemperature = (MU / (-log(PHI))) * this->currentSolution->getCost();
    this->temperature = this->originalTemperature;
    this->coolDownIteration = 0;
    this->neig_gen = 0;
    this->neig_success = 0;
    this->allTimeNeig = 0;
}

ProblemManager::~ProblemManager() {
    delete this->distanceMatrix;
    if (this->bestSolutionEver != this->currentSolution) {
        delete this->bestSolutionEver;
    }
    delete this->currentSolution;
}


/* TODO: Questions
 *
 * LINK: https://cv.usc.es/pluginfile.php/78242/mod_resource/content/7/4_4_MH_SA_16_17.pdf
 *
 * Here I don't know how to apply the correct algorithm explained by the teacher
 *
 *      -Should we generate solutions for the solution we have as the current one always?
 *
 *      -When should we return a solution?
 *
 *      -Does the "cool down for" exist?
 *
 *      -Should we return the current solution or the generated on each loop?
 *
 *      -Are we sure we need to stop at 10000 solutions generated?
 *
 *      -What happens if we generate all solutions without taking one
 *       and we cannot get a new one from the current solution?
 *
 * */
Solution *ProblemManager::getNextSolution() {

    Solution *candidateSolution = nullptr;

    //for (;;) {
    candidateSolution = this->currentSolution->getNextNeighbour(this->distanceMatrix);
    if (candidateSolution == nullptr) {
        std::cerr << "We have generated all the possible solutions of the current solution, this kind of should never have happened :(" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->allTimeNeig++;
    this->neig_gen++;

    int delta = candidateSolution->getCost() - this->currentSolution->getCost();

    const double EulerConstant = std::exp(1.0);

    double exponential = pow(EulerConstant, ((-delta) / this->temperature));

    double randomValue = rGen->getRandomDouble();

    if (delta < 0 || randomValue < exponential) {
        //We take the solution as the current one
        if (this->currentSolution != this->bestSolutionEver) {
            delete this->currentSolution;
        }
        this->currentSolution = candidateSolution;
        this->neig_success++;
    }
    //}

    //We update out best solution ever on each iteration
    if (this->currentSolution->getCost() < this->bestSolutionEver->getCost()) {
        delete this->bestSolutionEver;
        this->bestSolutionEver = this->currentSolution;
    }

    updateTemperature();

    return candidateSolution;
}


Solution *ProblemManager::getCurrentSolution() {
    return this->currentSolution;
}


Solution *ProblemManager::getBestSolutionEver() {
    return this->bestSolutionEver;
}

void ProblemManager::coolDown() {
    this->temperature = this->originalTemperature / (1 + this->coolDownIteration++);
}

void ProblemManager::updateTemperature() {

    if (neig_gen > MAX_NEIG) {
        this->neig_gen = 0;
        this->coolDown();
    }

    if (neig_success > MAX_SUCCESES) {
        this->neig_success = 0;
        this->coolDown();
    }

    return;
}

bool ProblemManager::showMustGoOn() {
    return (this->allTimeNeig < INTERNAL_ITERATIONS);
}


