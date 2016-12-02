/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Solution.h
 * Author: ruben.osorio0
 *
 * Created on 18 de noviembre de 2016, 16:04
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "LowerTriangularMatrix.h"
#include <utility>
#include <vector>

class Solution {
public:
    Solution();

    /**
     * Data must have its memory allocated outside the function.
     * @param data
     */
    Solution(int *data, pair<int, int> p, int previousCost, LowerTriangularMatrix<int> *distanceMatrix);

    virtual ~Solution();

    Solution *getNextNeighbour(LowerTriangularMatrix<int> *distanceMatrix);

    void print();

    void setCost(int cost);

    int getCost();

    unsigned int getElemAt(int pos);

    pair<int, int> getGenePair();

    void setProblemIteration(int ite);

    int getProblemIteration();

    void resetIte();

    void setData(int *newdata);


private:
    int *data;
    int cost;
    int currIter;
    pair<int, int> genePair;
    int problemIteration;

    void switchValues(int *data, pair<int, int> p);

    int getCostSwitching(std::pair<int, int> p, int previousCost, LowerTriangularMatrix<int> *distanceMatrix);

};

#endif /* SOLUTION_H */

