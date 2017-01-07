//
// Created by Rubén Osorio López on 2/1/17.
//

#include "Population.hpp"
#include "RandomGanerator.h"
#include "SolutionHelper.h"
#include "utils/timsort.hpp"

extern unsigned int problemIteration;
extern RandomGanerator *rGen;
extern int sizeOfProblem;


Population::~Population() {
    auto it = this->individuals.begin();

    while (it != this->individuals.end()) {
        delete (*it);
        it = this->individuals.erase(it);
    }

}

Population::Population(unsigned int size) {
    this->size = size;
}

void Population::generateFirstPopulation() {

    if (this->size != REAL_POPULATION_SIZE) {
        cerr << "Cannot initialize the population with a wrong size" << endl;
        exit(EXIT_FAILURE);
    }

    {   //We initialize the first half completely random

        for (int i = 0; i < REAL_POPULATION_SIZE / 2; i++) {
            Solution *newIndividual = new Solution(problemIteration);
            newIndividual->setData(rGen->getRandomArray());
            this->individuals.push_back(newIndividual);
        }
    }

    {   //We initialize the second half with a random city as the first and a greedy data after that

        for (int i = REAL_POPULATION_SIZE / 2; i < REAL_POPULATION_SIZE; i++) {
            Solution *newIndividual = new Solution(problemIteration);
            setGreedyDataButFirst(newIndividual);
            this->individuals.push_back(newIndividual);
        }
    }

}


void Population::generateRandomPopulationButOne(Solution *solution) {

    if (this->size != REAL_POPULATION_SIZE) {
        cerr << "Cannot initialize the population with a wrong size" << endl;
        exit(EXIT_FAILURE);
    }

    this->addIndividual(solution);

    {   //We initialize the first half completely random minus one solution

        for (int i = 1; i < REAL_POPULATION_SIZE / 2; i++) {
            Solution *newIndividual = new Solution(problemIteration);
            newIndividual->setData(rGen->getRandomArray());
            this->individuals.push_back(newIndividual);
        }
    }

    {   //We initialize the second half with a random city as the first and a greedy data after that

        for (int i = REAL_POPULATION_SIZE / 2; i < REAL_POPULATION_SIZE; i++) {
            Solution *newIndividual = new Solution(problemIteration);
            setGreedyDataButFirst(newIndividual);
            this->individuals.push_back(newIndividual);
        }
    }
}

void Population::evaluateWholePopulation() {

    for (int i = 0; i < this->individuals.size(); i++) {
        this->individuals.at(i)->setCost(calculateCostOf(this->individuals[i]));
    }

}

void Population::printPopulation() {
    for (int i = 0; i < this->individuals.size(); i++) {
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
    if (indiv_a->getCost() <= indiv_b->getCost()) {  //This could use a '<' or a '<='
        cout << position_a << endl;
        return new Solution(indiv_a, problemIteration);
    } else {
        cout << position_b << endl;
        return new Solution(indiv_b, problemIteration);
    }
}


void Population::addIndividual(Solution *solution) {
    this->individuals.push_back(solution);
}

void Population::addIndividualAtFront(Solution *solution) {
    this->individuals.push_front(solution);

}

void Population::doCross(int position_a, int position_b, double random) {
    Solution *indiv_a = this->individuals.at((unsigned long) position_a);
    Solution *indiv_b = this->individuals.at((unsigned long) position_b);

    cout << "\t\tPADRE: = ";
    indiv_a->printSimpleIndividual();
    cout << "\t\tPADRE: = ";
    indiv_b->printSimpleIndividual();

    if (random < CROSS_LIMIT) {

        //We generate a pair with the cut values
        pair<int, int> cuts;
        cuts.first = rGen->getRandomCross();
        cuts.second = rGen->getRandomCross();
        cout << "\t\tCORTES: (" << cuts.first << ", " << cuts.second << ")" << endl;
        if (cuts.first > cuts.second) {
            int aux = cuts.first;
            cuts.first = cuts.second;
            cuts.second = aux;
        }


        //Now we do the crossing
        int *genome_a = this->doOrderCrossover(cuts, indiv_a, indiv_b);
        int *genome_b = this->doOrderCrossover(cuts, indiv_b, indiv_a);

        indiv_a->setData(genome_a);
        indiv_b->setData(genome_b);

        indiv_a->setCost(calculateCostOf(indiv_a));
        indiv_b->setCost(calculateCostOf(indiv_b));


        cout << "\t\tHIJO: = ";
        indiv_a->printSimpleIndividual();
        cout << "\t\tHIJO: = ";
        indiv_b->printSimpleIndividual();


    } else {
        cout << "\t\tNO SE CRUZA" << endl;
    }

    cout << endl;
}

void Population::doMutation(int position) {

    Solution *indiv = this->individuals.at((unsigned long) position);


    cout << "\tRECORRIDO ANTES: ";
    indiv->printData();
    cout << endl;

    for (int i = 0; i < (sizeOfProblem - 1); i++) {
        double random = rGen->getRandomDouble();
        cout << "\t\tPOSICION: " << i << " (ALEATORIO " << random << ") ";

        if (random < MUTATION_LIMIT) {
            int position = rGen->getRandomCross();
            indiv->switchValues(pair<int, int>(i, position));
            cout << "INTERCAMBIO CON: " << position << endl;

        } else {
            cout << "NO MUTA" << endl;
        }

    }


    cout << "\tRECORRIDO DESPUES: ";
    indiv->printData();
    cout << endl;

}


bool isInGenome(int value, int *genome) {
    for (int i = 0; i < (sizeOfProblem - 1); i++) {
        if (value == genome[i]) return true;
    }
    return false;
}

/**
 * In "bool first": 1 generates the first son and 2 the second one
 *
 * */
int *Population::doOrderCrossover(pair<int, int> cuts, Solution *indiv_a, Solution *indiv_b) {
    int *newGenome = (int *) malloc(sizeof(int) * (sizeOfProblem - 1));
    for (int i = 0; i < (sizeOfProblem - 1); i++) {
        newGenome[i] = -1;
    }

    int *genome_a = indiv_a->getData();
    int *genome_b = indiv_b->getData();


    for (int i = cuts.first; i <= cuts.second; i++) {
        newGenome[i] = genome_a[i];
    }

    int newGenomePosition = (cuts.second + 1) % (sizeOfProblem - 1);
    int oldGenomePosition = newGenomePosition;

    while (newGenomePosition != cuts.first) {

        int possibleValue = genome_b[oldGenomePosition];
        while (isInGenome(possibleValue, newGenome)) {
            oldGenomePosition = (oldGenomePosition + 1) % (sizeOfProblem - 1);
            possibleValue = genome_b[oldGenomePosition];
        }
        newGenome[newGenomePosition] = possibleValue;
        newGenomePosition = (newGenomePosition + 1) % (sizeOfProblem - 1);
    }


    return newGenome;
}

Solution *Population::getIndividualAt(int position) {
    return this->individuals.at(position);
}

void Population::mergePopulations(Population *population, unsigned int sizelimit) {


    for (int i = 0; i < population->realSizeOfPopulation(); i++) {
        Solution *oldIndividual = population->getIndividualAt(i);
        Solution *newIndividual = new Solution(oldIndividual, oldIndividual->getProblemIteration());
        this->addIndividual(newIndividual);
    }

    this->sortPopulation();

    this->individuals.resize(sizelimit);


}

unsigned int Population::realSizeOfPopulation() {
    return (unsigned int) this->individuals.size();
}

void Population::generateRandomPopulationButTwo(Solution *solution, Solution *solution2) {

    if (this->size != REAL_POPULATION_SIZE) {
        cerr << "Cannot initialize the population with a wrong size" << endl;
        exit(EXIT_FAILURE);
    }

    this->addIndividual(solution);
    this->addIndividual(solution2);

    {   //We initialize the first half completely random minus one solution

        for (int i = 2; i < 20 + (REAL_POPULATION_SIZE / 2); i++) {
            Solution *newIndividual = new Solution(problemIteration);
            newIndividual->setData(rGen->getRandomArray());
            this->individuals.push_back(newIndividual);
        }
    }

    {   //We initialize the second half with a random city as the first and a greedy data after that

        for (int i = 20 + (REAL_POPULATION_SIZE / 2); i < REAL_POPULATION_SIZE; i++) {
            Solution *newIndividual = new Solution(problemIteration);
            setGreedyDataButFirst(newIndividual);
            this->individuals.push_back(newIndividual);
        }
    }

}









