//
// Created by Lorne Zhang on 11/26/20.
//

#include "Matrix2D.h"
#include <iostream>
#include <ctime>

/**
 * Matrix2D constructor
 * @param r num rows
 * @param c num columns
 */
Matrix2D::Matrix2D(int r, int c) {
    this-> rows = r;
    this-> cols = c;
    std::vector< std::vector<long> > m( rows, std::vector<long>(cols));
    this-> matrix = m;

    for(int i=0; i<rows; i++) {
        std::vector<long> mrow(cols);
        for(int j=0; j<cols; j++) {
            mrow[j] = rand() % 100;
        }
        matrix[i] = mrow;
    }
}

/**
 * Print matrix
 */
void Matrix2D::print() {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std:: cout << "" << std::endl;
    }
}

/**
 * Get number rows
 * @return rows
 */
int Matrix2D::getRow() {
    return rows;
}

/**
 * Get number columns
 * @return cols
 */
int Matrix2D::getCol() {
    return cols;
}

/**
 * Multiply two matrices
 * @param m matrix
 * @return multiplied matrix
 */
Matrix2D Matrix2D::multiply(Matrix2D m) {
    std::clock_t start;
    double duration;
    start = std::clock();

    if(cols != m.getRow()) {
        return Matrix2D(0,0);
    }
    Matrix2D m_multiplied(rows, m.getCol());
    for(int i=0; i<rows; i++) {
        for(int j=0; j<m.getCol(); j++) {
            long dot = 0;
            for(int k=0; k<cols; k++) {
                dot += matrix[i][k] * m.matrix[k][j];
            }
            m_multiplied.matrix[i][j] = dot;
        }
    }
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    printf("Duration: %f\n", duration);
    return m_multiplied;
}