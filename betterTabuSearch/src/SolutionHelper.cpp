//
// Created by Rubén Osorio López on 2/12/16.
//

#include "SolutionHelper.h"
#include "DistanceMatrixWrapper.h"


extern LowerTriangularMatrix<int> *globDistanceMatrix;
extern int sizeOfProblem;


int getClosestCity(int source, vector<int> *validList) {

    int city = -1;
    float cost = std::numeric_limits<float>::max();;

    for (std::vector<int>::const_iterator i = validList->begin(); i != validList->end(); ++i) {
        float costAux = getWeightedCost((unsigned int) source, (unsigned int) (*i));
        if ((costAux < cost) /*&& ((*i) != source)*/) {
            city = (*i);
            cost = costAux;

        }
    }
    return city;
}

//extern LowerTriangularMatrix<int> *frecMatrix;


void setGreedyData(Solution *solution) {


    int accumCost = 0;

    LowerTriangularMatrix<int> *localDistanceMatrix = globDistanceMatrix;

    int localSizeOfProblem = sizeOfProblem;

    int *array = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));
    vector<int> validList;

    for (int i = 1; i < (localSizeOfProblem); i++) {
        validList.push_back(i);
    }

    int value;

    value = getClosestCity(0, &validList);
    array[0] = value;
    validList.erase(std::remove(validList.begin(), validList.end(), value), validList.end());
    accumCost += localDistanceMatrix->getElement(0, (unsigned int) array[0]);

    for (int i = 0; i < sizeOfProblem - 2; i++) {
        value = getClosestCity(array[i], &validList);
        validList.erase(std::remove(validList.begin(), validList.end(), value), validList.end());
        array[i + 1] = value;
        accumCost += localDistanceMatrix->getElement((unsigned int) array[i], (unsigned int) array[i + 1]);
    }
    accumCost += localDistanceMatrix->getElement((unsigned int) array[sizeOfProblem - 2], 0);


    solution->setData(array);
    solution->setCost(accumCost);
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

    value = getClosestCity(0, &validList);
    array[0] = value;
    validList.erase(std::remove(validList.begin(), validList.end(), value), validList.end());

    for (int i = 0; i < sizeOfProblem - 2; i++) {
        value = getClosestCity(array[i], &validList);
        validList.erase(std::remove(validList.begin(), validList.end(), value), validList.end());
        array[i + 1] = value;
    }

    return array;
}
