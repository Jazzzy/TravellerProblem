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
#include "TabuList.hpp"

using namespace std;

int sizeOfProblem = 100;
RandomGanerator *rGen;
int maxNeig;
TabuList *tabuList;

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


    /*auto vec = tabuList->getAllValidPairs();
    for (std::vector<pair<int, int>>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << "[" << (*i).first << ',' << (*i).second << "] ";*/

    cout << endl;


    Solution *currentSolution;

    while ((currentSolution = PM->getNextSolution()) != nullptr) {
        currentSolution->print();
    }


    delete PM;
    delete rGen;

    return 0;
}

