#ifndef DISTANCEFILEPARSER_H
#define DISTANCEFILEPARSER_H

#include <vector>
#include "LowerTriangularMatrix.h"


void fillMatrix(char *path, LowerTriangularMatrix<int> *matrix);

void fillVectorOfRandoms(char *path, std::vector<float> *vector);

int getSizeOfProblem(char *path);

#endif	// DISTANCEFILEPARSER_H

