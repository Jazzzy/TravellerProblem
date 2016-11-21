//
// Created by jazzzy on 11/20/16.
//

#include <algorithm>
#include <iostream>
#include "TabuList.hpp"

using namespace std;

TabuList::TabuList(int size) {
    this->size = size;
    resetLists();

}

void TabuList::addElement(pair<int, int> p) {
    this->tabuList.push_back(p);
    this->validList.erase(remove(this->validList.begin(), this->validList.end(), p), this->validList.end());
    //cout << "erased: " << p.first << "," << p.second << endl;
}

TabuList::~TabuList() {


}

vector<pair<int, int>> TabuList::getAllValidPairs() {
    return this->validList;
}

void TabuList::resetTabu() {
    resetLists();
}

void TabuList::resetLists() {
    this->tabuList.clear();
    for (unsigned int i = 1; i < this->size; i++) {
        for (unsigned int j = 0; j < i; j++) {
            this->validList.push_back(make_pair(i, j));
        }
    }
}

void TabuList::print() {

    cout << "TABU LIST: " << endl;
    auto vec = this->tabuList;
    for (std::vector<pair<int, int>>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << "" << (*i).first << ',' << (*i).second << "" << endl;

    cout << "VALID LIST: " << endl;
    vec = this->validList;
    for (std::vector<pair<int, int>>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << "" << (*i).first << ',' << (*i).second << "" << endl;


}

vector<pair<int, int>> *TabuList::getAllValidPairsRef() {
    return &this->validList;
}


