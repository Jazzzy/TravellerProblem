//
// Created by Rubén Osorio López on 2/1/17.
//

#include "Population.hpp"
#include "RandomGanerator.h"
#include "SolutionHelper.h"
#include "utils/timsort.hpp"


extern RandomGanerator *rGen;

Population::~Population() {
    //TODO: Delete unused individuals
    //delete this->individuals;
}

Population::Population(unsigned int size) {
    this->size = size;
    this->individuals.reserve(size);
}

void Population::generateFirstPopulation() {

    if (this->size != REAL_POPULATION_SIZE) {
        cerr << "Cannot initialize the population with a wrong size" << endl;
        exit(EXIT_FAILURE);
    }

    {   //We initialize the first half completely random

        for (int i = 0; i < REAL_POPULATION_SIZE / 2; i++) {
            Solution *newIndividual = new Solution();
            newIndividual->setData(rGen->getRandomArray());
            this->individuals.push_back(newIndividual);
        }

    }

    {   //We initialize the second half with a random city as the first and a greedy data after that

        for (int i = REAL_POPULATION_SIZE / 2; i < REAL_POPULATION_SIZE; i++) {
            Solution *newIndividual = new Solution();
            setGreedyDataButFirst(newIndividual);
            this->individuals.push_back(newIndividual);
        }
    }

}

void Population::evaluateWholePopulation() {

    for (int i = 0; i < REAL_POPULATION_SIZE; i++) {
        this->individuals.at(i)->setCost(calculateCostOf(this->individuals[i]));
    }

}

void Population::printFirstPopulation() {
    cout << "POBLACION INICIAL" << endl;
    for (int i = 0; i < REAL_POPULATION_SIZE; i++) {
        cout << "INDIVIDUO " << i << " = ";
        this->individuals.at(i)->printSimpleIndividual();
    }
}


/**
 * Sorting algorithm from:
 *
 * https://github.com/swenson/sort
 *
 * Since we needed specifically timsort and it is not in C++
 *
 * */
void Population::sortPopulation() {

    gfx::timsort(this->individuals.begin(), this->individuals.end(), [](Solution *a, Solution *b) {
        return (a->getCostConst() < b->getCostConst());
    });

}

Solution *Population::doTournament(int position_a, int position_b) {

    cout << position_a << " " << position_b << " GANA ";


    Solution *indiv_a = this->individuals.at((unsigned long) position_a);
    Solution *indiv_b = this->individuals.at((unsigned long) position_b);
    if (indiv_a->getCost() < indiv_b->getCost()) {  //This could use a '<' or a '<='
        cout << position_a << endl;
        return new Solution(indiv_a);
    } else {
        cout << position_b << endl;
        return new Solution(indiv_b);
    }

}

void Population::addIndividual(Solution *solution) {
    this->individuals.push_back(solution);
}
