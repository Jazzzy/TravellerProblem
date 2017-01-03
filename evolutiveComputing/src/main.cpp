#include <cstdlib>
#include <cfenv>
#include "FileParser.h"
#include "RandomGanerator.h"
#include "ProblemManager.hpp"
#include <cfenv>

using namespace std;

int sizeOfProblem = 10;
RandomGanerator *rGen;
unsigned int problemIteration;


int main(int argc, char **argv) {

    ProblemManager *PM;

    cout << setprecision(6) << fixed;
    std::fesetround(FE_TONEAREST);


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


    while (PM->showMustGoOn()) {
        //OUTPUT
        PM->doAndPrint_SELECCION();
        PM->doAndPrint_CROSS();
        PM->doAndPrint_MUTATION();
        PM->doAndPrint_REPLACEMENT();
    }

    {   //OUTPUT
        PM->calcAndPrintBestIndividual();
    }

    delete PM;
    delete rGen;
    return EXIT_SUCCESS;
}

