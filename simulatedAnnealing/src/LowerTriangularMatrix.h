#pragma once

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

template<typename T>
class LowerTriangularMatrix {
public:
    LowerTriangularMatrix(unsigned int size);

    virtual ~LowerTriangularMatrix();

    T getElement(unsigned int x, unsigned int y);

    T getElementUnsafe(unsigned int x, unsigned int y);

    void setElement(unsigned int x, unsigned int y, T element);

    unsigned int getSize();

    void resetData();

    void printData();

    T getMax();

    T getMin();

    double getMean();

    double getStdDev();

private:
    unsigned int triangleNumber(unsigned int n);
    unsigned int insidePosition(unsigned int x, unsigned int y);
    void cleanArray();
    T *data;
    unsigned int size;
    unsigned int realSize;
};

template<typename T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(unsigned int size) {
    this->size = size;
    this->realSize = triangleNumber(size);
    this->data = (T *) malloc(sizeof(T) * realSize);
    cleanArray();
}

template<typename T>
void LowerTriangularMatrix<T>::resetData() {
    cleanArray();
}

template<typename T>
void LowerTriangularMatrix<T>::cleanArray() {
    for (unsigned int i = 0; i < realSize; i++) {
        this->data[i] = {};
    }
}

template<typename T>
T LowerTriangularMatrix<T>::getMax() {
    T currentMax=data[0];
    for (unsigned int i = 0; i < realSize; i++) {
        if(this->data[i]>currentMax){
            currentMax=this->data[i];
        }
    }
    return currentMax;
}

template<typename T>
T LowerTriangularMatrix<T>::getMin() {
    T currentMin=data[0];
    for (unsigned int i = 0; i < realSize; i++) {
        if(this->data[i]<currentMin){
            currentMin=this->data[i];
        }
    }
    return currentMin;
}



template<typename T>
LowerTriangularMatrix<T>::~LowerTriangularMatrix() {
    free(this->data);
}

template<typename T>
unsigned int LowerTriangularMatrix<T>::getSize() {
    return this->size;
}

template<typename T>
unsigned int LowerTriangularMatrix<T>::triangleNumber(unsigned int n) {
    if (n <= 0) {
        return 0;
    }

    return ((n * (n - 1) / 2));
}

template<typename T>
T LowerTriangularMatrix<T>::getElement(unsigned int x, unsigned int y) {
    if (x == y) {
        return T();
    }
    return (this->data[insidePosition(x, y)]);
}

template<typename T>
T LowerTriangularMatrix<T>::getElementUnsafe(unsigned int x, unsigned int y) {
    if (x == y) {
        return T();
    }
    return (this->data[triangleNumber(x) + y]);
}

template<typename T>
unsigned int LowerTriangularMatrix<T>::insidePosition(unsigned int x, unsigned int y) {
    if (x >= y) {
        return (triangleNumber(x) + y);
    } else {
        return (triangleNumber(y) + x);
    }
}

template<typename T>
void LowerTriangularMatrix<T>::setElement(unsigned int x, unsigned int y, T element) {

    this->data[insidePosition(x, y)] = element;
}

template<typename T>
void LowerTriangularMatrix<T>::printData() {
    for (unsigned int i = 1; i < this->size; i++) {
        for (unsigned int j = 0; j < i; j++) {
            cout << " [" << std::setfill(' ') << std::setw(6) << getElement(i, j) << "   ] ";
        }
        cout << endl;
    }
}

template<typename T>
double LowerTriangularMatrix<T>::getMean(){
    T sum=0;
    for (unsigned int i = 0; i < realSize; i++) {
        sum+=this->data[i];
    }
    return sum/realSize;
}

template<typename T>
double LowerTriangularMatrix<T>::getStdDev(){
    double mean = this->getMean();
    double stdDev=0;
    for(int i = 0; i < realSize; ++i)
        stdDev += pow(this->data[i] - mean, 2);

    return sqrt(stdDev / realSize);
}