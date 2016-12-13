//
// Created by Rubén Osorio López on 12/12/16.
//

#include "PairList.hpp"
#include <iostream>

PairList::PairList(int size) {
    this->size = size;
    this->validList.clear();
    for (int i = 1; i < this->size; i++) {
        for (int j = 0; j < i; j++) {
            this->validList.push_back(std::make_pair(i, j));
        }
    }
}

PairList::~PairList() {

}

std::vector<std::pair<int, int>> *PairList::getAllValidPairsRef() {
    return &(this->validList);
}

void PairList::print() {

    auto vec = this->validList;
    for (std::vector<std::pair<int, int>>::const_iterator i = vec.begin(); i != vec.end(); ++i)
    std::cout << "\n\t" << (*i).first << ' ' << (*i).second;

}

