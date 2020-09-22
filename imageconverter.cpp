//
// Created by Lorne Zhang on 9/20/20.
//

#include "imageconverter.h"
#include "job.h"
#include <iostream>

ImageConverter::ImageConverter(char const * bmp, string ascii) : Job() {
    this -> bmpFile = bmp;
    this -> asciiFile = ascii;
}


void ImageConverter::run() {
    // unsigned char image[MAXWIDTH][MAXHEIGHT];
    unsigned char image[MAXLENGTH];
    char ascii[32][32];

    int i;
    FILE* f = fopen(bmpFile, "rb");
    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    cout << width << " " << height << endl;

    // allocate 3 bytes per pixel
    int size = width * height * 3;
    // read the rest of the data at once
    fread(image, sizeof(unsigned char), size, f);
    fclose(f);


//    ifstream file(pngFile, ios::binary);
//    ifstream fileCheck(pngFile, ios::binary);
//    fileCheck.seekg( 0, ios::end );
//    size_t size = fileCheck.tellg();
//    cout << "File size: " << size << endl;
//
//    char* data = 0;
//    data = new char[ size - 8 + 1 ];
//    fileCheck.seekg( 8 ); // skip the header
//    fileCheck.read( data, size-8 );
//    data[ size-8 ] = '\0';
//    std::cout << "Data size: " << ((unsigned long long)fileCheck.tellg() - 8) << std::endl;
//
//    if (fileCheck)
//        std::cout << "all characters read successfully.\n";
//    else
//        std::cout << "error: only " << file.gcount() << " could be read\n";
//
//    unsigned int width, height;
//
//    file.seekg(16);
//    file.read((char *)&width, 4);
//    file.read((char *)&height, 4);
//
//    //file.close();
//
//    width = ntohl(width); // network byte to host byte
//    height = ntohl(height);
//
//    ifstream im;
//    im.open(pngFile, ios::binary);
//    file.seekg(16);
//
//    for(int i=0; i<height; i++) {
//        for(int j=0; j<width; j++) {
//            // image[i][j] = im.get();
//            image[i] = file.get();
//            // cout<<image[i][j]<<endl;
//        }
//    }
//
//    file.close();
//
//
//    cout << "got image" << endl;
//    cout << width << " " << height << endl;
    if(width > MAXWIDTH || height > MAXHEIGHT)
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
void ImageConverter::convertImage(unsigned char image[], int rowref, int colref, char ascii[32][32]) {
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


    int row = 0;
    int c = 0;
    for(int i=0; i<rowref; i++){
        int col = 0;
        for(int j=0; j<colref; j++) {
            int r = image[(i * colref + j*3)];
            int g = image[(i * colref + j)*3 + 1];
            int b = image[(i * colref + j)*3 + 2];
            int currVal = (r + g + b) / 3;
//            if(currVal > ascii_4) {
//                ascii[row][col] = '#'; // Darkest
//            }
//            else if(currVal > ascii_3) {
//                ascii[row][col] = 'o';
//            }
//            else if(currVal > ascii_2) {
//                ascii[row][col] = ':';
//            }
            if(currVal > 0) {
                ascii[row][col] = '*';
            }
            else {
                ascii[row][col] = ' '; // Lightest
                c++;
            }
            col ++;
        }
        row ++;
    }
    cout << c << endl;
}

/**
 * Shrinks the image to the appropriate size
 * @param image - image 2D array
 * @param rowref - number of rows
 * @param colref - number of columns
 */
void ImageConverter::processImage(unsigned char image[], int rowref, int colref) {
    unsigned char shrunkImage[32][32];
    int rowIncrement = (rowref / 32);
    int colIncrement = (colref / 32);
    int numRows = 0;
    int numCols = 0;
    for(int i=0; i<rowref-rowIncrement; i+=rowIncrement) {
        numCols = 0;
        for(int j=0; j<colref-colIncrement; j+=colIncrement) {
            numCols ++;
            if(numCols == 32) break;
            shrunkImage[numRows][numCols] = image[(i*colref + j)*3 + 2];
        }
        numRows ++;
        if(numRows == 32) break;
    }
    for(int i=0; i<numRows; i++) {
        for(int j=0; j<numCols; j++) {
            // cout << i*numRows + j << endl;
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
void ImageConverter::writeImage(string &asciiFileName, char ascii[32][32], int rowref, int colref) {
    fstream output(asciiFileName.c_str(), ios :: out); // create fstream to write text file
    for(int i=0; i<32; i++) {
        for(int j=0; j<32; j++) {
            output << ascii[i][j];
        }
        output << endl;
    }
    output.close();
}