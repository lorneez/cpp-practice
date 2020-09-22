//
// Created by Lorne Zhang on 9/20/20.
//

#ifndef DAILYPROGRAMMER_IMAGECONVERTER_H
#define DAILYPROGRAMMER_IMAGECONVERTER_H

#define MAXHEIGHT 1000
#define MAXWIDTH 1000
#define MAXLENGTH 1000000
#include "job.h"
#include <iostream>
#include <fstream>

using namespace std;

class ImageConverter : public Job {
public:
    ImageConverter(char const * bmp, string ascii);
    virtual void run();
    virtual void indicateTaken();

private:
    void processImage(unsigned char image[MAXLENGTH], int rowref, int colref);
    void convertImage(unsigned char image[MAXLENGTH],int rowref, int colref, char ascii[32][32]);
    void writeImage(string& textFileName, char ascii[32][32], int rowref, int colref);
    const char* bmpFile;
    string asciiFile;
};


#endif //DAILYPROGRAMMER_IMAGECONVERTER_H
