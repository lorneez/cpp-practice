//
// Created by Lorne Zhang on 11/27/20.
//

#ifndef DAILYPROGRAMMER_MATRIXVECTOR_H
#define DAILYPROGRAMMER_MATRIXVECTOR_H


#include <vector>

class MatrixVector {
public:
    MatrixVector(int n, std::vector<int> d);
    void initializeMatrix();
    int get(int a);
    int get(int a, int b);
    int get(int a, int b, int c);
    void test();

private:
    int numDimensions;
    std::vector<int> dimensions;
    std::vector<int> matrixVector;
};


#endif //DAILYPROGRAMMER_MATRIXVECTOR_H
