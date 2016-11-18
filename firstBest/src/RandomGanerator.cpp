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
    this->readFromFile = false;
}


RandomGanerator::RandomGanerator(char *file) {

    //TODO: Implement reading the numbers from a file.
}

int *RandomGanerator::getRandomArray() {

    if (!readFromFile) {
        srand(time(NULL));
        int *array = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));

        std::vector<int> aux(10);
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

        //TODO

        return nullptr;

    }
}


std::pair<int, int> RandomGanerator::getRandomPair() {
    if (!readFromFile) {
        std::pair<int, int> p = std::make_pair(((rand() % (sizeOfProblem - 1))), ((rand() % (sizeOfProblem - 1))));
        //std::cout << p.first << "," << p.second << std::endl;
        return p;
    } else {

        //TODO

        return std::make_pair(-1, -1);

    }
}


RandomGanerator::~RandomGanerator() {
    if (readFromFile) {
        //close everything or free the random numbers stored.
    }
}

