//
// Created by Rubén Osorio López on 2/1/17.
//

#ifndef TRAVELLERPROBLEM_EVOLUTIVE_COMPUTING_POPULATION_HPP
#define TRAVELLERPROBLEM_EVOLUTIVE_COMPUTING_POPULATION_HPP


#include "Solution.h"
#include <deque>


#define REAL_POPULATION_SIZE 100
#define CROSS_LIMIT 0.9
#define MUTATION_LIMIT 0.01


class Population {
public:

    Population(unsigned int size);

    ~Population();

    void generateFirstPopulation();

    void evaluateWholePopulation();

    void printPopulation();

    void sortPopulation();

    void addIndividual(Solution *solution);

    void addIndividualAtFront(Solution *solution);


    Solution *doTournament(int position_a, int position_b);

    Solution *getIndividualAt(int position);

    void doCross(int position_a, int position_b, double random);

    void doMutation(int position);


private:
    std::deque<Solution *> individuals;
    unsigned int size;

    int *doOrderCrossover(pair<int, int> cuts, Solution *indiv_a, Solution *indiv_b);

};


#endif //TRAVELLERPROBLEM_EVOLUTIVE_COMPUTING_POPULATION_HPP
