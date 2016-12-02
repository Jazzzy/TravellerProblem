//
// Created by Rubén Osorio López on 2/12/16.
//

#include "SolutionHelper.h"


extern LowerTriangularMatrix<int> *globDistanceMatrix;
extern int sizeOfProblem;


int getClosestCity(int source, LowerTriangularMatrix<int> *localDistanceMatrix, vector<int> *validList) {

    int city = -1;
    int cost = std::numeric_limits<int>::max();;

    for (std::vector<int>::const_iterator i = validList->begin(); i != validList->end(); ++i) {
        int costAux = localDistanceMatrix->getElement((unsigned int) source, (unsigned int) (*i));
        if ((costAux < cost) /*&& ((*i) != source)*/) {
            city = (*i);
            cost = costAux;

        }
    }
    return city;
}

int *getGreedyData() {

    LowerTriangularMatrix<int> *localDistanceMatrix = globDistanceMatrix;

    int localSizeOfProblem = sizeOfProblem;

    int *array = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));
    vector<int> validList;

    for (int i = 1; i < (localSizeOfProblem); i++) {
        validList.push_back(i);
    }

    int value;

    value = getClosestCity(0, localDistanceMatrix, &validList);
    array[0] = value;
    validList.erase(std::remove(validList.begin(), validList.end(), value), validList.end());

    for (int i = 0; i < sizeOfProblem - 2; i++) {
        value = getClosestCity(array[i], localDistanceMatrix, &validList);
        validList.erase(std::remove(validList.begin(), validList.end(), value), validList.end());
        array[i + 1] = value;
    }

    return array;
}
