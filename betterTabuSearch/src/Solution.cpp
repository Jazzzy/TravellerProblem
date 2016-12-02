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
#include "SolutionHelper.h"


using namespace std;

extern int sizeOfProblem;
extern RandomGanerator *rGen;
extern int maxNeig;
extern TabuList *tabuList;

Solution::Solution() {
    /*this->data = getGreedyData();
    this->cost = -1;*/
    setGreedyData(this);
    this->currIter = 0;
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

    if (currIter >= (tabuList->getAllValidPairsRef()->size())) {
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

void Solution::resetIte() {
    this->currIter = 0;
}

void Solution::setData(int *newdata) {
    this->data = newdata;
}














