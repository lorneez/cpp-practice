//
// Created by Lorne Zhang on 11/26/20.
//

#ifndef DAILYPROGRAMMER_MATRIX2D_H
#define DAILYPROGRAMMER_MATRIX2D_H
#include<vector>

class Matrix2D {
public:
    Matrix2D(int r, int c);
    Matrix2D multiply(Matrix2D m);
    void print();
    int getRow();
    int getCol();
    std::vector< std::vector<long> > matrix; // create 2D matrix representation with vectors
private:
    int rows;
    int cols;
};


#endif //DAILYPROGRAMMER_MATRIX2D_H
