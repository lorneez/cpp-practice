//
// Created by Lorne Zhang on 9/20/20.
//

#include "imageconverter.h"
#include "../MultiThreading/job.h"
#include <iostream>
#include <vector>
#include <cmath>

ImageConverter::ImageConverter(char const * bmp, string ascii) : Job() {
    this -> bmpFile = bmp;
    this -> asciiFile = ascii;
}

void ImageConverter::run() {
    unsigned char image[MAXLENGTH];
    char ascii[MAXIMAGESIZE][MAXIMAGESIZE];
    unsigned char info[54];

    ifstream inp{ bmpFile, ios_base::binary };
    FILE* f = fopen(bmpFile, "rb");

    fread(info, sizeof(unsigned char), 54, f);
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    int offset = *(int*)&info[14];
    int size = 3 * width * height;

    inp.seekg(offset, inp.beg);

    for(int i=0; i<size; i++) {
        image[i] = inp.get();
    }

    if(width > MAXIMAGESIZE || height > MAXIMAGESIZE)
    {
        processImage(image, height, width);
    }
    convertImage(image, height, width, ascii);
    writeImage(asciiFile,ascii,height,width);
}

void ImageConverter::indicateTaken() {

}

/**
 * Converts the image 2D array into an ascii 2D array
 * @param image - image 2D array
 * @param rowref - number of rows
 * @param colref - number of columns
 * @param ascii - ascii 2D array
 */
void ImageConverter::convertImage(unsigned char image[], int rowref, int colref, char ascii[MAXIMAGESIZE][MAXIMAGESIZE]) {
    int maxImageVal = image[0];
    int minImageVal = maxImageVal;

    for(int i=0; i<rowref; i++) {
        for(int j=0; j<colref; j++) {
            int currVal = image[i * colref + j];
            if(currVal > maxImageVal) {
                maxImageVal = currVal;
            }
            if(currVal < minImageVal) {
                minImageVal = currVal;
            }
        }
    }

    // define 5 sections of ascii symbols
    int ascii_spectrum_width = ((maxImageVal - minImageVal) / 5);
    int ascii_1 = (minImageVal + ascii_spectrum_width);
    int ascii_2 = ((ascii_1 + 1) + ascii_spectrum_width);
    int ascii_3 = ((ascii_2 + 1) + ascii_spectrum_width);
    int ascii_4 = ((ascii_3 + 1) + ascii_spectrum_width);

    int row = 0;
    for(int i=0; i<MAXIMAGESIZE; i++){
        int col = 0;
        for(int j=0; j<MAXIMAGESIZE; j++) {
            int currVal = image[(i * colref + j)];
            if(currVal > ascii_4) {
                ascii[row][col] = ' ';
            }
            else if(currVal > ascii_3) {
                ascii[row][col] = '.';
            }
            else if(currVal > ascii_2) {
                ascii[row][col] = ':';
            }
            else if(currVal > ascii_1) {
                ascii[i][j] = 'o';
            }
            else {
                ascii[i][j] = '#';
            }
            col ++;
        }
        row ++;
    }
}

/**
 * Shrinks the image to the appropriate size
 * @param image - image 2D array
 * @param rowref - number of rows
 * @param colref - number of columns
 */
void ImageConverter::processImage(unsigned char image[], int rowref, int colref) {
    unsigned char shrunkImage[MAXIMAGESIZE][MAXIMAGESIZE];
    int rowIncrement = (rowref / MAXIMAGESIZE);
    int colIncrement = (colref / MAXIMAGESIZE);
    int numRows = 0;
    int numCols = 0;
    for(int i=0; i<rowref-rowIncrement; i+=rowIncrement) {
        numCols = 0;
        for(int j=0; j<colref-colIncrement; j+=colIncrement) {
            numCols ++;
            if(numCols == MAXIMAGESIZE) break;

            double r = (double)image[i*colref + j * 3 + 2];
            double g = (double)image[i*colref + j * 3 + 1];
            double b = (double)image[i*colref + j * 3];
            r = r * 0.299;
            g = g * 0.587;
            b = b * 0.144;

            unsigned char gray = floor((r + g + b + 0.5));
            shrunkImage[numRows][numCols] = gray;
        }
        numRows ++;
        if(numRows == MAXIMAGESIZE) break;
    }

    for(int i=0; i<numRows; i++) {
        for(int j=0; j<numCols; j++) {
            image[numRows * i + j] = shrunkImage[i][j];
        }
    }
}

/**
 * Writes Ascii 2D array into a text file
 * @param asciiFileName - name of the ascii file
 * @param ascii - ascii 2D array
 * @param rowref - number of rows
 * @param colref - number of columns
 */
void ImageConverter::writeImage(string &asciiFileName, char ascii[MAXIMAGESIZE][MAXIMAGESIZE], int rowref, int colref) {
    fstream output(asciiFileName.c_str(), ios :: out); // create fstream to write text file
    for(int i=0; i<MAXIMAGESIZE; i++) {
        for(int j=0; j<MAXIMAGESIZE; j++) {
            output << ascii[i][j];
        }
        output << endl;
    }
    output.close();
}