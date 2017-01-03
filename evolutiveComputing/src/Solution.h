#ifndef SOLUTION_H
#define SOLUTION_H

#include "LowerTriangularMatrix.h"
#include <utility>
#include <vector>

class Solution {
public:

    Solution(unsigned int problemIteration);

    Solution(Solution *original, unsigned int problemIteration);

    virtual ~Solution();

    void setCost(int cost);

    int getCost();

    const int getCostConst() const;

    void setData(int *newdata);

    void printData();

    int getElemAt(int pos);

    void printSimpleIndividual();

    void switchValues(pair<int, int> p);

    int *getData();

    unsigned int getProblemIteration();


private:
    int *data;
    int cost;
    unsigned int problemIteration;
};

#endif /* SOLUTION_H */

