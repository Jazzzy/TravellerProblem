/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RandomGanerator.h
 * Author: ruben.osorio0
 *
 * Created on 18 de noviembre de 2016, 16:27
 */

#ifndef RANDOMGANERATOR_H
#define RANDOMGANERATOR_H
#include <utility>

class RandomGanerator {
public:
    RandomGanerator();
    RandomGanerator(char * file);
    int* getRandomArray();
    std::pair<int,int> getRandomPair();
    virtual ~RandomGanerator();
private:
    bool readFromFile;
    

};

#endif /* RANDOMGANERATOR_H */

