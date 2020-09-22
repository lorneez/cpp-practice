//
// Created by Lorne Zhang on 9/20/20.
//

#ifndef DAILYPROGRAMMER_IMAGECONVERTER_H
#define DAILYPROGRAMMER_IMAGECONVERTER_H

#define MAXHEIGHT 500
#define MAXWIDTH 500
#define MAXLENGTH 250000
#include "job.h"
#include <iostream>
#include <fstream>

using namespace std;

class ImageConverter : public Job {
public:
    ImageConverter(string jpeg, string ascii);
    virtual void run();
    virtual void indicateTaken();

private:
    void processImage(unsigned char image[MAXLENGTH], int rowref, int colref);
    void convertImage(unsigned char image[MAXLENGTH],int rowref, int colref, char ascii[100][100]);
    void writeImage(string& textFileName, char ascii[100][100], int rowref, int colref);
    string pngFile;
    string asciiFile;
};


#endif //DAILYPROGRAMMER_IMAGECONVERTER_H
