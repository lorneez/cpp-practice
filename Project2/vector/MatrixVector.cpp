//
// Created by Lorne Zhang on 11/27/20.
//

#include "MatrixVector.h"
#include <iostream>

MatrixVector::MatrixVector(int n, std::vector<int> d) {
    this->numDimensions = n;
    this->dimensions = d;
    initializeMatrix();
}

void MatrixVector::initializeMatrix() {
    int totalSize = 1;
    for(int i : dimensions) {
        totalSize *= i;
    }
    this->matrixVector = std::vector<int>(totalSize);
    for(int i=0; i<totalSize; i++) {
        matrixVector[i] = numDimensions;
    }
}

int MatrixVector::get(int a) {
    if(a >= dimensions[0]) {
        std::cout << "Incorrect dimensions" << std::endl;
        return -1;
    }
    return matrixVector[a]; // return a
}

int MatrixVector::get(int a, int b) {
    if(a >= dimensions[0] || b >= dimensions[1]) {
        std::cout << "Incorrect dimensions" << std::endl;
        return -1;
    }
    return matrixVector[a + b*dimensions[0]]; // return a + number of rows b
}

int MatrixVector::get(int a, int b, int c) {
    if(a >= dimensions[0] || b >= dimensions[1] || c >= dimensions[2]) {
        std::cout << "Incorrect dimensions" << std::endl;
        return -1;
    }
    return matrixVector[a + b*dimensions[0] + c*dimensions[0]*dimensions[1]]; // return a + number of rows b + number of slices c
}

void MatrixVector::test() {
    MatrixVector m1(1,std::vector<int>{3});
    MatrixVector m2(2,std::vector<int>{3,3});
    MatrixVector m3(3,std::vector<int>{3,3,3});
    std::cout << "1D" << std::endl;
    for(int i=0; i<m1.dimensions[0]; i++) {
        std::cout << m1.get(i);
    }
    std::cout << std::endl;
    std::cout << "2D" << std::endl;
    for(int i=0; i<m2.dimensions[0]; i++) {
        for(int j=0; j<m2.dimensions[1]; j++) {
            std::cout << m2.get(i,j);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "3D" << std::endl;
    for(int i=0; i<m3.dimensions[0]; i++) {
        for(int j=0; j<m3.dimensions[1]; j++) {
            for(int k=0; k<m3.dimensions[2]; k++) {
                std::cout << m3.get(i,j,k);
            }
            std::cout << " ";
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}