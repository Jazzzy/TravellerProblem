//
// Created by jazzzy on 11/20/16.
//

#include <algorithm>
#include <iostream>
#include "TabuList.hpp"
#include <vector>

using namespace std;



bool compare(const pair<int, int> &i, const pair<int, int> &j) {
    if (i.first < j.first) return true;
    else if (i.first == j.first && i.second < j.second) return true;
    return false;
}


TabuList::TabuList(int size) {
    this->size = size;
    resetLists();
}

void TabuList::removeFirst() {
    pair<int, int> p = this->tabuList.front();
    this->tabuList.erase(this->tabuList.begin());

    //Insert the element in the correct position.
    this->validList.insert(std::lower_bound(this->validList.begin(), this->validList.end(), p, compare), p);

}

void TabuList::addElement(pair<int, int> p) {

    if (tabuList.size() >= TABU_LIST_SIZE) {
        removeFirst();
    }

    this->tabuList.push_back(p);
    this->validList.erase(remove(this->validList.begin(), this->validList.end(), p), this->validList.end());
}

TabuList::~TabuList() {


}


void TabuList::resetTabu() {
    resetLists();
}

void TabuList::resetLists() {
    this->tabuList.clear();
    this->validList.clear();
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

void TabuList::printFormatted() {

    auto vec = this->tabuList;
    for (std::vector<pair<int, int>>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << "\n\t" << (*i).first << ' ' << (*i).second;

}



