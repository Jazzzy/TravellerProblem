#include "Solution.h"
#include "RandomGanerator.h"
#include "SolutionHelper.h"
#include "PairList.hpp"


using namespace std;

extern int sizeOfProblem;
extern RandomGanerator *rGen;
extern PairList *pList;


Solution::Solution() {
    setGreedyData(this);
    this->bestNeighbour = nullptr;
}

Solution::Solution(int *data, pair<int, int> p, int previousCost, LowerTriangularMatrix<int> *distanceMatrix) {
    this->data = data;
    this->genePair = p;
    this->cost = getCostSwitching(p, previousCost, distanceMatrix);
    this->currIter = 0;
    this->bestNeighbour = nullptr;
}

Solution::~Solution() {
    free(this->data);
    return;
}

void Solution::printData() {
    for (int i = 0; i < sizeOfProblem - 1; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

Solution *Solution::getNextNeighbour(LowerTriangularMatrix<int> *distanceMatrix) {
    Solution *newSolution = nullptr;

    if (currIter >= (pList->getAllValidPairsRef()->size())) {
        return nullptr;
    }
    std::pair<int, int> p = pList->getAllValidPairsRef()->at((unsigned long) currIter);
    currIter++;
    int *newData = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));
    memcpy(newData, this->data, sizeof(int) * (sizeOfProblem - 1));
    newSolution = new Solution(newData, p, this->getCost(), distanceMatrix);
    return newSolution;

}


void Solution::switchValues(int *data, pair<int, int> p) {
    int aux = data[p.first];
    data[p.first] = data[p.second];
    data[p.second] = aux;
    return;
}


void Solution::setCost(int cost) {
    this->cost = cost;
}

int Solution::getCost() {
    return this->cost;
}

unsigned int Solution::getElemAt(int pos) {
    return (unsigned int) this->data[pos];
}


pair<int, int> Solution::getGenePair() {
    return this->genePair;
}


int Solution::getCostSwitching(std::pair<int, int> p, int previousCost, LowerTriangularMatrix<int> *distanceMatrix) {


    int minusCost = 0;
    int plusCost = 0;


    if (p.second == 0) {

        minusCost += distanceMatrix->getElement(0, getElemAt(p.second));
        minusCost += distanceMatrix->getElement(getElemAt(p.second), getElemAt(p.second + 1));


    } else {

        minusCost += distanceMatrix->getElement(getElemAt(p.second - 1), getElemAt(p.second));
        minusCost += distanceMatrix->getElement(getElemAt(p.second), getElemAt(p.second + 1));

    }

    if (p.first == sizeOfProblem - 2) {

        minusCost += distanceMatrix->getElement(getElemAt(p.first), 0);
        minusCost += distanceMatrix->getElement(getElemAt(p.first - 1), getElemAt(p.first));

    } else {

        minusCost += distanceMatrix->getElement(getElemAt(p.first), getElemAt(p.first + 1));
        minusCost += distanceMatrix->getElement(getElemAt(p.first - 1), getElemAt(p.first));
    }


    unsigned int oldi = (unsigned int) getElemAt(p.first);
    unsigned int oldj = (unsigned int) getElemAt(p.second);
    switchValues(this->data, p);


    if (p.second == 0) {


        plusCost += distanceMatrix->getElement(0, oldi);
        plusCost += distanceMatrix->getElement(oldi, getElemAt(p.second + 1));


    } else {


        plusCost += distanceMatrix->getElement(getElemAt(p.second - 1), oldi);
        plusCost += distanceMatrix->getElement(oldi, getElemAt(p.second + 1));

    }


    if (p.first == (sizeOfProblem - 2)) {

        plusCost += distanceMatrix->getElement(oldj, 0);
        plusCost += distanceMatrix->getElement(getElemAt(p.first - 1), oldj);


    } else {

        plusCost += distanceMatrix->getElement(oldj, getElemAt(p.first + 1));
        plusCost += distanceMatrix->getElement(getElemAt(p.first - 1), oldj);

    }

    return previousCost - minusCost + plusCost;
}


void Solution::setData(int *newdata) {
    this->data = newdata;
}


void Solution::print() {
    //cout << endl << "ITERACION: " << this->getProblemIteration() + 1 << endl;
    cout << "\tINTERCAMBIO: (" << this->getGenePair().first << ", " << this->getGenePair().second << ")" << endl
         << "\tRECORRIDO: ";
    this->printData();
    cout << "\tFUNCION OBJETIVO (km): " << this->getCost() << endl;
}

void Solution::printSimple() {
    cout << "\tRECORRIDO: ";
    this->printData();
    cout << "\tFUNCION OBJETIVO (km): " << this->getCost() << endl;
}

void Solution::printSimpleWIte() {
    cout << "\tRECORRIDO: ";
    this->printData();
    cout << "\tFUNCION OBJETIVO (km): " << this->getCost() << endl;
    cout << "\tITERACION: " << this->problemIteration << endl;
}

int Solution::getProblemIteration() {
    return this->problemIteration;
}

void Solution::setProblemIteration(int iteration) {
    this->problemIteration = iteration;
}

Solution *Solution::getBestNeighbour(LowerTriangularMatrix<int> *distanceMatrix) {

    if (!this->bestNeighbour) {
        Solution *newSolution = this->getNextNeighbour(distanceMatrix);
        Solution *currentBest = newSolution;

        newSolution = this->getNextNeighbour(distanceMatrix);

        while (newSolution != nullptr) {
            if (currentBest->getCost() > newSolution->getCost()) {
                delete currentBest;
                currentBest = newSolution;
            } else {
                delete newSolution;
            }
            newSolution = this->getNextNeighbour(distanceMatrix);
        }

        this->bestNeighbour = currentBest;
    }

    return this->bestNeighbour;

}















