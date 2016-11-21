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
    Solution(int *data, pair<int, int> p);

    virtual ~Solution();

    Solution *getNextNeighbour();

    void print();

    void setCost(int cost);

    int getCost();

    int getElemAt(int pos);

    pair<int, int> getGenePair();

    int getCurrIte();

private:

    vector<pair<int,int>> possiblePairs;

    int *data;
    int cost;
    int currIter;
    pair<int, int> genePair;

    //LowerTriangularMatrix<bool> *visitedNeig;

    bool isValidNeig(pair<int, int> p);

    pair<int, int> getNextPair(pair<int, int> p);

    pair<int, int> sortPair(pair<int, int> p);

    void switchValues(int *data, pair<int, int> p);



};

#endif /* SOLUTION_H */

