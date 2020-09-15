//
// Created by Lorne Zhang on 9/14/20.
//

#include "mandelbrot.h"
#include <iostream>
#include <fstream> // for files manipulation
#include <complex> // for complex numbers
using namespace std;

Mandelbrot::Mandelbrot(double width, double height) {
    this -> width = width;
    this -> height = height;
}

double Mandelbrot::MapToReal(int x) {
    // 0-width -> minReal-maxReal
    double range = maxReal - minReal;
    // x / width -> fraction in 0->width
    // fraction * range -> 0-range
    // 0-range + minReal -> minReal-maxReal
    double fraction = x / width;
    double zerorange = fraction * range;
    double mapped = zerorange + minReal;
    return mapped;

}

double Mandelbrot::MapToImaginary(int y) {
    double range = maxImaginary - minImaginary;
    double fraction = y / height;
    double zerorange = fraction * range;
    double mapped = zerorange + minImaginary;
    return mapped;
}

int Mandelbrot::CheckMandelbrot(double cr, double ci) {
    int iterations = 0;
    double zr = 0.0;
    double zi = 0.0;
    while(iterations < maxIterations && zr * zr + zi * zi < 4.0) {
        double temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        iterations++;
    }
    return iterations;
}

void Mandelbrot::Display() {
    ofstream fout("generated_image.ppm");
    fout << "P3" << endl;
    fout << width << " " << height << endl;
    fout << maxRGB << endl;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            double cr = MapToReal(x);
            double ci = MapToImaginary(y);
            int iterations = CheckMandelbrot(cr, ci);
            int r = ((int) (sinf(iterations)) % 256);
            int g = ((int) (cosf(iterations)) % 256);
            int b = (iterations * iterations % 256);
            fout << r << " " << g << " " << b << endl;
        }
        cout << x << endl;
        fout << endl;
    }
    fout.close();
}