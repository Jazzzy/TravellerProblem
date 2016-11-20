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
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <math.h>

using namespace std;

extern int sizeOfProblem;
extern RandomGanerator *rGen;
extern int maxNeig;
extern TabuList *tabuList;

Solution::Solution() {
    this->data = rGen->getRandomArray();
    this->visitedNeig = new LowerTriangularMatrix<bool>((unsigned int) (sizeOfProblem - 1));
    this->cost = -1;
    this->currIter = 0;
    this->possiblePairs = tabuList->getAllValidPairs();


    /*auto vec = possiblePairs;
    for (std::vector<pair<int, int>>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << "[" << (*i).first << ',' << (*i).second << "]\n";*/
}

Solution::Solution(int *data, pair<int, int> p) {
    this->data = data;
    this->visitedNeig = new LowerTriangularMatrix<bool>((unsigned int) (sizeOfProblem - 1));
    this->cost = -1;
    this->currIter = 0;
    this->genePair = p;
    this->possiblePairs = tabuList->getAllValidPairs();
}

Solution::~Solution() {
    delete this->visitedNeig;
    free(this->data);
}

void Solution::print() {
    cout << "[" << data[0];
    for (int i = 1; i < sizeOfProblem - 1; i++) {
        cout << ", " << data[i];
    }
    cout << "];";
}

Solution *Solution::getNextNeighbour() {

    if (currIter >= (this->possiblePairs.size() - 1)) {
        return nullptr;
    }


    /*auto vec = this->possiblePairs;
    for (std::vector<pair<int, int>>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << "[" << (*i).first << ',' << (*i).second << "] ";*/

    pair<int, int> p = this->possiblePairs.at(currIter);

    cout << p.first << "," << p.second << endl;

    //this->possiblePairs.erase(this->possiblePairs.begin() + currIter);

    currIter++;


    this->visitedNeig->setElement((unsigned int) p.first, (unsigned int) p.second, true);

    int *newData = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));

    memcpy(newData, this->data, sizeof(int) * (sizeOfProblem - 1));

    switchValues(newData, p);

    Solution *newSolution = new Solution(newData, p);

    return newSolution;

    /*if (currIte >= maxNeig) {
        return nullptr;
    }

    pair<int, int> p = rGen->getRandomPair();
    p = sortPair(p);

    while (!isValidNeig(p)) {
        p = getNextPair(p);
    }

    currIte++;
    this->visitedNeig->setElement((unsigned int) p.first, (unsigned int) p.second, true);
    int *newData = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));
    memcpy(newData, this->data, sizeof(int) * (sizeOfProblem - 1));
    switchValues(newData, p);
    Solution *newSolution = new Solution(newData, p);

    return newSolution;*/

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

bool Solution::isValidNeig(pair<int, int> p) {
    if ((p.first == p.second))
        return false;
    bool b = this->visitedNeig->getElement((unsigned int) p.first, (unsigned int) p.second);
    return !b;
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











