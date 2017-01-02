#include <cstdlib>
#include "FileParser.h"
#include "RandomGanerator.h"
#include "ProblemManager.hpp"
#include "Population.hpp"

using namespace std;

int sizeOfProblem = 10;
RandomGanerator *rGen;


int main(int argc, char **argv) {

    ProblemManager *PM;

    if (argc < 2) {
        cerr << "We need a file that contains the distances" << endl;
        return 1;
    } else if (argc == 2) {
        rGen = new RandomGanerator();
        PM = new ProblemManager(argv[1]);
    } else if (argc == 3) {
        rGen = new RandomGanerator(argv[2]);
        PM = new ProblemManager(argv[1]);
    } else {
        cerr << "Too many arguments." << endl;
        return EXIT_FAILURE;
    }


    {   //OUTPUT
        PM->printInitialPopulation();
    }

    PM->doAndPrint_SELECCION();


    while (PM->showMustGoOn()) {

        {   //OUTPUT
        }
    }

    {   //OUTPUT
    }

    delete PM;
    delete rGen;
    return EXIT_SUCCESS;
}

