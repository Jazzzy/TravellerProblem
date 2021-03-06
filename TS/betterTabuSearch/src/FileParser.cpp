/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DistanceFileParser.cpp
 * Author: ruben.osorio0
 * 
 * Created on 11 de noviembre de 2016, 17:44
 */



#include "FileParser.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>

using std::cout;
using std::endl;

#include <fstream>

using std::ifstream;


extern int sizeOfProblem;


const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 150;
const char *const DELIMITER = "\t";

void fillMatrix(char *path, LowerTriangularMatrix<int> *matrix) {

    ifstream inputStream;
    inputStream.open(path);
    if (!inputStream.good())
        std::runtime_error("Could not open file");

    int row = 1;

    while (!inputStream.eof()) {

        char buf[MAX_CHARS_PER_LINE];
        inputStream.getline(buf, MAX_CHARS_PER_LINE);

        int n = 0;

        const char *token[MAX_TOKENS_PER_LINE] = {};

        token[0] = strtok(buf, DELIMITER);
        if (token[0]) {
            for (n = 1; n < MAX_TOKENS_PER_LINE; n++) {
                token[n] = strtok(0, DELIMITER);
                if (!token[n]) break;
            }
        }

        for (int i = 0; i < n; i++) {
            matrix->setElement(row, i, atoi(token[i]));
        }

        row++;

    }
    sizeOfProblem = row - 1;
}

const int MAX_CHARS_PER_LINE2 = 64;
const int MAX_TOKENS_PER_LINE2 = 2;
const char *const DELIMITER2 = "\n";

void fillVectorOfRandoms(char *path, std::vector<float> *vector) {

    ifstream inputStream;
    inputStream.open(path);
    if (!inputStream.good())
        std::runtime_error("Could not open file");

    int row = 1;

    while (!inputStream.eof()) {

        char buf[MAX_CHARS_PER_LINE2];
        inputStream.getline(buf, MAX_CHARS_PER_LINE2);

        int n = 0;

        const char *token[MAX_TOKENS_PER_LINE2] = {};

        token[0] = strtok(buf, DELIMITER2);
        if (token[0]) {
            for (n = 1; n < MAX_TOKENS_PER_LINE2; n++) {
                token[n] = strtok(0, DELIMITER2);
                if (!token[n]) break;
            }
        }

        for (int i = 0; i < n; i++) {
            vector->push_back(atof(token[i]));
        }
        row++;
    }

    return;
}


int getSizeOfProblem(char *path) {

    ifstream inputStream;
    inputStream.open(path);
    if (!inputStream.good())
        std::runtime_error("Could not open file");

    int row = 0;

    while (!inputStream.eof()) {
        char buf[MAX_CHARS_PER_LINE];
        inputStream.getline(buf, MAX_CHARS_PER_LINE);
        row++;
    }
    return row;

}
