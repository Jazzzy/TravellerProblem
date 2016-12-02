//
// Created by Rubén Osorio López on 2/12/16.
//

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

    int maxFrec = frecMatrix->getMax();
    if(maxFrec==0){
        return realCost;
    }
    float weightedCost = realCost + MU * differenceInDist * (frecMatrix->getElement(x, y) / maxFrec);

    return weightedCost;

}

void addFrec(unsigned int x, unsigned int y) {
    frecMatrix->setElement(x, y, frecMatrix->getElement(x, y) + 1);
}

void destroyWrapper() {
    delete frecMatrix;
}