//
// Created by Rubén Osorio López on 2/12/16.
//

#include "SolutionHelper.h"
#include "DistanceMatrixWrapper.h"


extern LowerTriangularMatrix<int> *globDistanceMatrix;
extern int sizeOfProblem;


int getClosestCity(int source, vector<int> *validList) {

    int city = -1;
    float cost = std::numeric_limits<float>::max();

    /*if (source == 0) {
        cout << source << endl;
    }*/

    for (std::vector<int>::const_iterator i = validList->begin(); i != validList->end(); ++i) {
        float costAux = getWeightedCost((unsigned int) source, (unsigned int) (*i));
        if ((costAux < cost) /*&& ((*i) != source)*/) {
            city = (*i);
            cost = costAux;

        }
        /*if((*i)==98){
            cout << source << endl;
        }*/
    }
    return city;
}

/*//extern LowerTriangularMatrix<int> *frecMatrix;
int counterOfCities = 0;
int modules = 0;
int times = 0;
#define SAME_CITY_TIMES 3*/

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
    /*if (value != 98) {
        cout << value << endl;
        exit(1);
    }*/
    array[0] = value;



    //cout << "ARRAY 0: " << array[0] << endl;

    /*if ((times) > SAME_CITY_TIMES) {
        array[0] = (counterOfCities++ + (20 * modules++)) % (sizeOfProblem - 2);
        times = 0;
        printf("PILLAMOS OTRA: %d", array[0]);
    }
    times++;*/

    validList.erase(std::remove(validList.begin(), validList.end(), value), validList.end());
    accumCost += localDistanceMatrix->getElement(0, (unsigned int) array[0]);

    for (int i = 0; i < sizeOfProblem - 2; i++) {
        value = getClosestCity(array[i], &validList);
        validList.erase(std::remove(validList.begin(), validList.end(), value), validList.end());
        array[i + 1] = value;
        accumCost += localDistanceMatrix->getElement((unsigned int) array[i], (unsigned int) array[i + 1]);
    }
    accumCost += localDistanceMatrix->getElement((unsigned int) array[sizeOfProblem - 2], 0);

    //cout << "ARRAY 0: " << array[0] << endl;


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
