/* 
 * File:   DistanceFileParser.h
 * Author: ruben.osorio0
 *
 * Created on 11 de noviembre de 2016, 17:44
 */


#ifndef DISTANCEFILEPARSER_H
#define DISTANCEFILEPARSER_H
#include "LowerTriangularMatrix.h"
void fillMatrix(char * path,  LowerTriangularMatrix<int> *matrix);

int getSizeOfProblem(char * path);

#endif	// DISTANCEFILEPARSER_H

