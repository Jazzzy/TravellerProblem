#include "DistanceMatrixWrapper.h"
#include "LowerTriangularMatrix.h"

extern LowerTriangularMatrix<int> *globDistanceMatrix;
extern int sizeOfProblem;
LowerTriangularMatrix<int> *frecMatrix;


int differenceInDist;

void initWrapper() {
    differenceInDist = globDistanceMatrix->getMax() - globDistanceMatrix->getMin();
    frecMatrix = new LowerTriangularMatrix<int>((unsigned int) sizeOfProblem);
}

float getWeightedCost(unsigned int x, unsigned int y) {
    LowerTriangularMatrix<int> *localDistanceMatrix = globDistanceMatrix;
    int realCost = localDistanceMatrix->getElement(x, y);
    double maxFrec = frecMatrix->getMax();
    if (maxFrec == 0) {
        return realCost;
    }
    double frec= frecMatrix->getElement(x, y);
    double weightedCost = realCost + (MU2 * differenceInDist * ((frec / maxFrec)));
    return (float) weightedCost;
}

double frecParameter() {
    return frecMatrix->getStdDev();
}

void addFrec(unsigned int x, unsigned int y) {
    frecMatrix->setElement(x, y, (frecMatrix->getElement(x, y) + 1));
}

void destroyWrapper() {
    delete frecMatrix;
}