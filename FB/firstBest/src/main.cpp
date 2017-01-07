/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ruben.osorio0
 *
 * Created on 11 de noviembre de 2016, 16:26
 */

#include <cstdlib>
#include "FileParser.h"
#include "Solution.h"
#include "RandomGanerator.h"
#include "ProblemManager.hpp"

using namespace std;

int sizeOfProblem = 0;
RandomGanerator *rGen;
int maxNeig;

int main(int argc, char **argv) {

    ProblemManager *PM;

    if (argc < 2) {
        cerr << "We need a file that contains the distances\nExample: program ./distancias_10.txt" << endl;
        return 1;
    }

    if (argc == 2) {                            //We have the file with the distances
        rGen = new RandomGanerator();
        PM = new ProblemManager(argv[1]);
    } else if (argc == 3) {
        rGen = new RandomGanerator(argv[2]);
        PM = new ProblemManager(argv[1]);
    }


    Solution *currentSolution;
    while ((currentSolution = PM->getNextSolution()) != nullptr);


    delete PM;
    delete rGen;

    return 0;
}

