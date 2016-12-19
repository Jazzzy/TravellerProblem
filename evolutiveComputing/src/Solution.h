#ifndef SOLUTION_H
#define SOLUTION_H

#include "LowerTriangularMatrix.h"
#include <utility>
#include <vector>

class Solution {
public:
    Solution();

    virtual ~Solution();

    void setCost(int cost);

    int getCost();

    void setData(int *newdata);

    void printData();

    void print();

    void printSimple();

    void switchValues(int *data, pair<int, int> p);


private:
    int *data;
    int cost;
};

#endif /* SOLUTION_H */

