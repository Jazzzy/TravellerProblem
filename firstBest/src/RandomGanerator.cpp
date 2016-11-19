/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RandomGanerator.cpp
 * Author: ruben.osorio0
 * 
 * Created on 18 de noviembre de 2016, 16:27
 */

#include "RandomGanerator.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "FileParser.h"
#include <math.h>


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
        srand(time(NULL));
        int *array = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));

        std::vector<int> aux(9);
        std::generate(aux.begin(), aux.end(), Generator());
        std::vector<int>::const_iterator it, end = aux.end();

        int position;
        int currentElems = sizeOfProblem - 1;

        for (int i = 0; i < sizeOfProblem - 1; i++) {
            position = rand() % currentElems--;
            array[i] = aux.at(position);
            aux.erase(aux.begin() + (position));
        }


        return array;
    } else {

        int *array = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));

        std::vector<int> aux(9);
        std::generate(aux.begin(), aux.end(), Generator());
        std::vector<int>::const_iterator it, end = aux.end();

        int position;
        int value;

        for (int i = 0; i < sizeOfProblem - 1; i++) {

            float fvalue = floor(getNextReadFloat() * (float) (sizeOfProblem - 1));
            value = (int) fvalue + 1;

            while ((std::find(aux.begin(), aux.end(), value) == aux.end())) {
                value = (value + 1) % (sizeOfProblem - 1);
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


