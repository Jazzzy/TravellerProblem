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
#include "DistanceFileParser.h"
#include "Solution.h"
#include "RandomGanerator.h"
#include "ProblemManager.hpp"

using namespace std;

int sizeOfProblem = 0;
RandomGanerator *rGen;
int maxNeig;

int main(int argc, char **argv) {

    cout << endl;
    rGen = new RandomGanerator();
    ProblemManager *PM;

    if (argc < 2) {
        cerr << "We need a file that contains the distances\nExample: program ./distancias_10.txt" << endl;
        return 1;
    }

    if (argc == 2) {                                                //We have the file with the distances
        PM = new ProblemManager(argv[1]);
    }

    //cout << "Size of problem: " << sizeOfProblem << endl;
    //cout << "MAX NEIG: " << maxNeig << endl;

    Solution *currentSolution;
    while ((currentSolution = PM->getNextSolution()) != nullptr) {
        //currentSolution->print();
    }
    //cout << "Final Solution: " << endl << "\t";
    //PM->getCurrentSolution()->print();

    delete PM;


    return 0;
}

