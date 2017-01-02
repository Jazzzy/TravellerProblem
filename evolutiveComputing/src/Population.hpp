//
// Created by Rubén Osorio López on 2/1/17.
//

#ifndef TRAVELLERPROBLEM_EVOLUTIVE_COMPUTING_POPULATION_HPP
#define TRAVELLERPROBLEM_EVOLUTIVE_COMPUTING_POPULATION_HPP


#include "Solution.h"

#define REAL_POPULATION_SIZE 100

class Population {
public:

    Population(unsigned int size);

    ~Population();

    void generateFirstPopulation();

    void evaluateWholePopulation();

    void printFirstPopulation();

    void sortPopulation();

    void addIndividual(Solution *solution);

    Solution * doTournament(int position_a, int position_b);


private:
    std::vector<Solution*> individuals;
    unsigned int size;
};


#endif //TRAVELLERPROBLEM_EVOLUTIVE_COMPUTING_POPULATION_HPP
