#ifndef SOLUTION_H
#define SOLUTION_H

#include "LowerTriangularMatrix.h"
#include "ListOfNeighbours.hpp"
#include <utility>
#include <vector>

class ListOfNeighbours;

#define MODULE_SOLUTIONS 100
#define DIV_SOLUTION 5

class Solution {
public:
    Solution();

    /**
     * Data must have its memory allocated outside the function.
     * @param data
     */
    Solution(int *data, pair<int, int> p, int previousCost, LowerTriangularMatrix<int> *distanceMatrix);

    virtual ~Solution();

    void deleteAllListBut(Solution *dontDelete);

    Solution *getNextNeighbour(LowerTriangularMatrix<int> *distanceMatrix);

    Solution *getBestNeighbour(LowerTriangularMatrix<int> *distanceMatrix);

    void setCost(int cost);

    int getCost();

    unsigned int getElemAt(int pos);

    pair<int, int> getGenePair();

    void setData(int *newdata);

    int getProblemIteration();

    void setProblemIteration(int iteration);

    void printData();

    void print();

    void printSimple();

    void printSimpleWIte();

    void addFrequencyToMatrix();


private:
    int *data;
    int cost;
    pair<int, int> genePair;
    int problemIteration;
    int currIter;
    ListOfNeighbours *listOfNeighbours;

    int indexOfSolution;

    void switchValues(int *data, pair<int, int> p);

    int getCostSwitching(std::pair<int, int> p, int previousCost, LowerTriangularMatrix<int> *distanceMatrix);

};

#endif /* SOLUTION_H */

