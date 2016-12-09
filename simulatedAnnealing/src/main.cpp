#include <cstdlib>
#include "FileParser.h"
#include "Solution.h"
#include "RandomGanerator.h"
#include "ProblemManager.hpp"

using namespace std;

int sizeOfProblem = 100;
RandomGanerator *rGen;

#define ITERATIONS 10000

int main(int argc, char **argv) {

    ProblemManager *PM;

    if (argc < 2) {
        cerr << "We need a file that contains the distances" << endl;
        return 1;
    }

    if (argc == 2) {
        rGen = new RandomGanerator();
        PM = new ProblemManager(argv[1]);
    } else if (argc == 3) {
        rGen = new RandomGanerator(argv[2]);
        PM = new ProblemManager(argv[1]);
    }else{
        cerr << "Too many arguments." << endl;
        return EXIT_FAILURE;
    }

    Solution *currentSolution;
    currentSolution = PM->getCurrentSolution();

    {   //OUTPUT
        cout << "RECORRIDO INICIAL" << endl;
        currentSolution->printSimple();
    }


    for (int i = 0; i < ITERATIONS; i++) {
        currentSolution = PM->getNextSolution();

        {   //OUTPUT
            currentSolution->print();
        }
    }

    {   //OUTPUT
        cout << endl << endl << "MEJOR SOLUCION: " << endl;
       PM->getBestSolutionEver()->printSimpleWIte();
    }

    delete PM;
    delete rGen;
    return EXIT_SUCCESS;
}

