/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Solution.cpp
 * Author: ruben.osorio0
 * 
 * Created on 18 de noviembre de 2016, 16:04
 */

#include "Solution.h"
#include "RandomGanerator.h"
#include "TabuList.hpp"
#include <cstring>
#include <stdlib.h>


using namespace std;

extern int sizeOfProblem;
extern RandomGanerator *rGen;
extern int maxNeig;
extern TabuList *tabuList;

Solution::Solution() {
    this->data = rGen->getRandomArray();
    //this->visitedNeig = new LowerTriangularMatrix<bool>((unsigned int) (sizeOfProblem - 1));
    this->cost = -1;
    this->currIter = 0;
    //this->possiblePairs = tabuList->getAllValidPairs();


    /*auto vec = possiblePairs;
    for (std::vector<pair<int, int>>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << "[" << (*i).first << ',' << (*i).second << "]\n";*/
}

Solution::Solution(int *data, pair<int, int> p, int previousCost, LowerTriangularMatrix<int> *distanceMatrix) {
    this->data = data;
    this->currIter = 0;
    this->genePair = p;
    this->cost = getCostSwitching(p, previousCost, distanceMatrix);
}

Solution::~Solution() {
    free(this->data);
    return;
}

void Solution::print() {
    for (int i = 0; i < sizeOfProblem - 1; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

Solution *Solution::getNextNeighbour(LowerTriangularMatrix<int> *distanceMatrix) {
    if (currIter >= (tabuList->getAllValidPairsRef()->size() - 1)) {
        return nullptr;
    }

    pair<int, int> p = tabuList->getAllValidPairsRef()->at((unsigned long) currIter);
    currIter++;
    int *newData = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));
    memcpy(newData, this->data, sizeof(int) * (sizeOfProblem - 1));
    Solution *newSolution = new Solution(newData, p, this->getCost(), distanceMatrix);
    return newSolution;
}


void Solution::switchValues(int *data, pair<int, int> p) {
    int aux = data[p.first];
    data[p.first] = data[p.second];
    data[p.second] = aux;
    return;
}

pair<int, int> Solution::getNextPair(pair<int, int> p) {
    pair<int, int> aux = p;
    if ((p.first == p.second) || (p.first == (p.second - 1))) {
        aux.first++;
        aux.second = 0;
    } else {
        aux.second++;
    }
    if ((p.first >= (sizeOfProblem - 2)) && (p.second >= (sizeOfProblem - 3))) {
        aux.first = 1;
        aux.second = 0;
    }
    return aux;
}

pair<int, int> Solution::sortPair(pair<int, int> p) {
    if (p.second > p.first) {
        int aux = p.first;
        p.first = p.second;
        p.second = aux;
    }
    return p;
}


void Solution::setCost(int cost) {
    this->cost = cost;
}

int Solution::getCost() {
    return this->cost;
}

int Solution::getElemAt(int pos) {
    return this->data[pos];
}


pair<int, int> Solution::getGenePair() {
    return this->genePair;
}

int Solution::getCurrIte() {
    return currIter;
}

void Solution::setProblemIteration(int ite) {
    this->problemIteration = ite;
}

int Solution::getProblemIteration() {
    return this->problemIteration;
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


    int di = getElemAt(p.first);
    int dj = getElemAt(p.second);
    switchValues(this->data, p);


    if (p.second == 0) {


        plusCost += distanceMatrix->getElement(0, di);
        plusCost += distanceMatrix->getElement(di, getElemAt(p.second + 1));


    } else {


        plusCost += distanceMatrix->getElement(getElemAt(p.second - 1), di);
        plusCost += distanceMatrix->getElement(di, getElemAt(p.second + 1));

    }


    if (p.first == (sizeOfProblem - 2)) {

        plusCost += distanceMatrix->getElement(dj, 0);
        plusCost += distanceMatrix->getElement(getElemAt(p.first - 1), dj);


    } else {

        plusCost += distanceMatrix->getElement(dj, getElemAt(p.first + 1));
        plusCost += distanceMatrix->getElement(getElemAt(p.first - 1), dj);

    }

    return previousCost - minusCost + plusCost;
}














