#include "RandomGanerator.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include "FileParser.h"
#include "Population.hpp"


struct Generator {
    Generator() : m_value(1) {
    }

    int operator()() {
        return m_value++;
    }

    int m_value;
};

extern int sizeOfProblem;

RandomGanerator::RandomGanerator() {
    randVec = nullptr;
}


RandomGanerator::RandomGanerator(char *file) {
    randVec = new std::vector<float>();
    fillVectorOfRandoms(file, randVec);
}

float RandomGanerator::getNextReadFloat() {
    float number = randVec->front();
    randVec->erase(randVec->begin());
    return number;
}

int *RandomGanerator::getRandomArray() {

    if (!randVec) {
        srand((unsigned int) time(NULL));
        int *array = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));

        std::vector<int> aux((unsigned long) (sizeOfProblem - 1));
        std::generate(aux.begin(), aux.end(), Generator());
        std::vector<int>::const_iterator it, end = aux.end();

        int position;
        int currentElems = sizeOfProblem - 1;

        for (int i = 0; i < sizeOfProblem - 1; i++) {
            position = rand() % currentElems--;
            array[i] = aux.at((unsigned long) position);
            aux.erase(aux.begin() + (position));
        }


        return array;
    } else {
        int *array = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));

        std::vector<int> aux((unsigned long) (sizeOfProblem - 1));
        std::generate(aux.begin(), aux.end(), Generator());
        std::vector<int>::const_iterator it, end = aux.end();

        int value;

        for (int i = 0; i < sizeOfProblem - 1; i++) {

            float fvalue = floor(getNextReadFloat() * (float) (sizeOfProblem - 1));
            value = (int) fvalue + 1;

            while ((std::find(aux.begin(), aux.end(), value) == aux.end())) {
                value = (value + 1) % (sizeOfProblem);
            }
            aux.erase(std::remove(aux.begin(), aux.end(), value), aux.end());
            array[i] = value;
        }

        return array;
    }
}


std::pair<int, int> RandomGanerator::getRandomPair() {
    if (!randVec) {
        std::pair<int, int> p = std::make_pair(((rand() % (sizeOfProblem - 1))), ((rand() % (sizeOfProblem - 1))));
        return p;
    } else {
        float xf = getNextReadFloat();
        float yf = getNextReadFloat();

        int x = (int) floor(xf * (sizeOfProblem - 1));
        int y = (int) floor(yf * (sizeOfProblem - 1));

        return std::make_pair(x, y);
    }
}


RandomGanerator::~RandomGanerator() {
    if (randVec) {
        delete randVec;
    }
}

int RandomGanerator::getRandomInt() {
    if (randVec) {
        int value = (int) floor(getNextReadFloat() * (sizeOfProblem - 1));
        return value;
    } else {
        return (rand() % (sizeOfProblem - 1));
    }
}

double RandomGanerator::getRandomDouble() {
    if (randVec)
        return getNextReadFloat();
    else
        return (float) rand() / (float) (RAND_MAX);
}

int RandomGanerator::getRandomCity() {
    double random = getRandomDouble();
    if (random == 1.0) return (sizeOfProblem - 1);
    return (int) (floor((random * (sizeOfProblem - 1))) + 1);
}

int RandomGanerator::getRandomPosition() {
    double random = getRandomDouble();
    if (random == 1.0) return (REAL_POPULATION_SIZE - 1);

    return (int) floor(random * (REAL_POPULATION_SIZE));
}

int RandomGanerator::getRandomCross() {
    double random = getRandomDouble();
    if (random == 1.0) return (sizeOfProblem - 2);

    return (int) floor(random * (sizeOfProblem - 1));
}





