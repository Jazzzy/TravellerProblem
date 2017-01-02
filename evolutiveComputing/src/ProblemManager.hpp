#ifndef PROBLEMMANAGER_HPP
#define PROBLEMMANAGER_HPP


#include "Solution.h"
#include "Population.hpp"


class ProblemManager {
public:
    ProblemManager(char *pathOfDistances);

    virtual ~ProblemManager();

    bool showMustGoOn();

    void printInitialPopulation();

    void doAndPrint_SELECCION();

    void doAndPrint_CROSS();

    void doAndPrint_MUTATION();

    void doAndPrint_REPLACEMENT();


private:
    Population *currentPopulation;
    Population *newPopulation;

    LowerTriangularMatrix<int> *distanceMatrix;
    unsigned int problemIteration;
};


#endif
