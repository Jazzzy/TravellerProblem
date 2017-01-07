//
// Created by Rubén Osorio López on 13/12/16.
//

#ifndef TRAVELLERPROBLEM_SIMULATED_ANNEALING_BETTER_LISTOFNEIGHBOURS_HPP
#define TRAVELLERPROBLEM_SIMULATED_ANNEALING_BETTER_LISTOFNEIGHBOURS_HPP


#include "Solution.h"


class Solution;

struct SolutionNode {
    Solution *solution;
    SolutionNode *next;
};

class ListOfNeighbours {

public:
    ListOfNeighbours();

    virtual ~ListOfNeighbours();

    Solution *getSolutionAt(int position);

    void deleteAllBut(Solution *dontDelete);

    void insertSolution(Solution *solution);

    void printSolutions();


private:
    SolutionNode *firstElement;

};


#endif //TRAVELLERPROBLEM_SIMULATED_ANNEALING_BETTER_LISTOFNEIGHBOURS_HPP
