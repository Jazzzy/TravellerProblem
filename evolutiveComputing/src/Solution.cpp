#include "Solution.h"
#include "RandomGanerator.h"
#include "PairList.hpp"


using namespace std;

extern int sizeOfProblem;
extern RandomGanerator *rGen;
extern PairList *pList;


Solution::Solution() {
    this->cost = 0;
}

Solution::Solution(Solution *original) {
    this->data = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));
    memcpy(this->data, original->data, sizeof(int) * (sizeOfProblem - 1));
    this->cost = original->cost;
}

Solution::~Solution() {
    free(this->data);
    return;
}

void Solution::printData() {
    for (int i = 0; i < sizeOfProblem - 1; i++) {
        cout << data[i] << " ";
    }
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

void Solution::setData(int *newdata) {
    this->data = newdata;
}

int Solution::getElemAt(int pos) {
    return this->data[pos];
}

void Solution::printSimpleIndividual() {
    cout << "{FUNCION OBJETIVO (km): " << this->getCost() << ", RECORRIDO: ";
    this->printData();
    cout << "}" << endl;

}

const int Solution::getCostConst() const {
    return this->cost;
}





















