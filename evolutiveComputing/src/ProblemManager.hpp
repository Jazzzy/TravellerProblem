#ifndef PROBLEMMANAGER_HPP
#define PROBLEMMANAGER_HPP


#include "Solution.h"
#include "Population.hpp"
#define MAX_ITERATIONS 1000
#define ELITIST_NUMBER 2

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

    void calcAndPrintBestIndividual();


private:
    Population *currentPopulation;
    Population *newPopulation;

    LowerTriangularMatrix<int> *distanceMatrix;
};


#endif
