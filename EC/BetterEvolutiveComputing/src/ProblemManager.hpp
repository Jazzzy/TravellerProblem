#ifndef PROBLEMMANAGER_HPP
#define PROBLEMMANAGER_HPP


#include "Solution.h"
#include "Population.hpp"

#define MAX_ITERATIONS 1000
#define INIT_REINI_COUNTER 20

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

    void doAndPrint_REINICIALIZATION();

    void calcAndPrintBestIndividual();


private:
    Population *currentPopulation;
    Population *newPopulation;
    unsigned int reinicializationCounter;
    unsigned int numberOfReinitalizations;
    void reinitialize();

    LowerTriangularMatrix<int> *distanceMatrix;
};


#endif
