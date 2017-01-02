#ifndef SOLUTION_H
#define SOLUTION_H

#include "LowerTriangularMatrix.h"
#include <utility>
#include <vector>

class Solution {
public:

    Solution();

    Solution(Solution * original);

    virtual ~Solution();

    void setCost(int cost);

    int getCost();

    const int getCostConst() const;

    void setData(int *newdata);

    void printData();

    int getElemAt(int pos);

    void printSimpleIndividual();

    void switchValues(int *data, pair<int, int> p);


private:
    int *data;
    int cost;
};

#endif /* SOLUTION_H */

