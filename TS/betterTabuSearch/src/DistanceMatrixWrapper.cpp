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

    double maxFrec = frecMatrix->getMax();
    if (maxFrec == 0) {
        return realCost;
    }

    double frec= frecMatrix->getElement(x, y);
    double weightedCost = realCost + (MU * differenceInDist * ((frec / maxFrec)));

    return (float) weightedCost;
}

double frecParameter() {
    double ret = frecMatrix->getStdDev();
    //cout << "STDDEV:" << ret << endl;
    return ret;
}

void addFrec(unsigned int x, unsigned int y) {

    /*if (x == 0 && y == 98) {
        cout << "(0:98) "<<(frecMatrix->getElement(x, y)) << endl;
    }*/
    frecMatrix->setElement(x, y, (frecMatrix->getElement(x, y) + 1));
    /*if (x == 0 && y == 98) {
        cout << "(0:98) "<<(frecMatrix->getElement(x, y)) << endl;
    }*/

}

void destroyWrapper() {
    delete frecMatrix;
}