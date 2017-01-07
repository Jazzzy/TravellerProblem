//
// Created by Rubén Osorio López on 12/12/16.
//

#ifndef TRAVELLERPROBLEM_SIMULATED_ANNEALING_PAIRLIST_H
#define TRAVELLERPROBLEM_SIMULATED_ANNEALING_PAIRLIST_H


#include <vector>
#include <utility>

class PairList {
public:

    PairList(int size);

    virtual ~PairList();

    std::vector<std::pair<int, int>> *getAllValidPairsRef();

    void print();

private:

    std::vector<std::pair<int, int>> validList;
    int size;

};


#endif //TRAVELLERPROBLEM_SIMULATED_ANNEALING_PAIRLIST_H
