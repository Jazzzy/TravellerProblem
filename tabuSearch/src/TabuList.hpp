//
// Created by jazzzy on 11/20/16.
//

#ifndef TRAVELLERPROBLEM_TABUSEARCH_TABULIST_HPP
#define TRAVELLERPROBLEM_TABUSEARCH_TABULIST_HPP

#include <vector>
#include <utility>

#pragma once

using namespace std;

class TabuList {
public:
    TabuList(int size);

    virtual ~TabuList();

    vector<pair<int, int>> getAllValidPairs();

    vector<pair<int, int>> *getAllValidPairsRef();

    void addElement(pair<int, int> p);

    void resetTabu();

    void print();

private:
    vector<pair<int, int>> validList;
    vector<pair<int, int>> tabuList;
    int size;

    void resetLists();

};


#endif //TRAVELLERPROBLEM_TABUSEARCH_TABULIST_HPP
