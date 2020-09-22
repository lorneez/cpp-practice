//
// Created by Lorne Zhang on 9/20/20.
//

#include "imageconverter.h"
#include "job.h"
#include <iostream>

ImageConverter::ImageConverter(string png, string ascii) : Job() {
    this -> pngFile = png;
    this -> asciiFile = ascii;
}


void ImageConverter::run() {
    // unsigned char image[MAXWIDTH][MAXHEIGHT];
    unsigned char image[MAXLENGTH];
    char ascii[100][100];

    ifstream file(pngFile, ios::binary);
    unsigned int width, height;

    file.seekg(16);
    file.read((char *)&width, 4);
    file.read((char *)&height, 4);

    //file.close();

    width = ntohl(width); // network byte to host byte
    height = ntohl(height);

//    ifstream im;
//    im.open(pngFile, ios::binary);
//    file.seekg(16);

    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            // image[i][j] = im.get();
            image[i] = file.get();
            // cout<<image[i][j]<<endl;
        }
    }

    file.close();


    cout << "got image" << endl;
    cout << width << " " << height << endl;
    if(width > 100 || height > 100)
    {
        cout << "shrunk" << endl;
        processImage(image, height, width);
    }

    cout << "convert" << endl;
    convertImage(image, height, width, ascii);

    cout << "write" << endl;
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
void ImageConverter::convertImage(unsigned char image[], int rowref, int colref, char ascii[100][100]) {
    // initialize max and min to first pixel
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

    for(int i=0; i<rowref; i++){
        for(int j=0; j<colref; j++) {
            int currVal = image[i * colref + j];
            if(currVal > ascii_4) {
                ascii[i][j] = '#'; // Darkest
            }
            else if(currVal > ascii_3) {
                ascii[i][j] = 'o';
            }
            else if(currVal > ascii_2) {
                ascii[i][j] = ':';
            }
            else if(currVal > ascii_1) {
                ascii[i][j] = '.';
            }
            else {
                ascii[i][j] = ','; // Lightest
            }
        }
    }
}

/**
 * Shrinks the image to the appropriate size
 * @param image - image 2D array
 * @param rowref - number of rows
 * @param colref - number of columns
 */
void ImageConverter::processImage(unsigned char image[], int rowref, int colref) {
    unsigned char shrunkImage[100][100];
    int rowIncrement = (rowref / 100);
    int colIncrement = (colref / 100);

    int numRows = 0;
    int numCols = 0;

    for(int i=0; i<rowref-rowIncrement; i+=rowIncrement) {
        numCols = 0;
        for(int j=0; j<colref-colIncrement; j+=colIncrement) {

            // iterate through image and increment by 1/100 of image row and col size
            // find the average pixel value
            int sum = 0;
            int total = 0;
            for(int a=i; a<i+rowIncrement; a++) {
                for(int b=j; b<j+colIncrement; b++) {
                    cout << a << " " << b << endl;
                    cout << (colref * a + b) << endl;
                    sum += image[colref * a + b];
                    total++;
                }
            }

            numCols ++;
            if(numCols == 100) break;
            shrunkImage[numRows][numCols] = sum / total;

        }
        numRows ++;
        if(numRows == 100) break;
    }

    cout << numRows << " " << numCols << endl;

    for(int i=0; i<numRows; i++) {
        for(int j=0; j<numCols; j++) {
            cout << (colref * i + j) << endl;
            cout << i << " " << j << endl;
            image[colref * i + j] = shrunkImage[i][j];
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
void ImageConverter::writeImage(string &asciiFileName, char ascii[100][100], int rowref, int colref) {
    fstream output(asciiFileName.c_str(), ios :: out); // create fstream to write text file
    for(int i=0; i<rowref; i++) {
        for(int j=0; j<colref; j++) {
            output << ascii[i][j];
        }
        output << endl;
    }
    output.close();
}