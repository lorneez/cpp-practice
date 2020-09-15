//
// Created by Lorne Zhang on 9/14/20.
//

#ifndef DAILYPROGRAMMER_MANDELBROT_H
#define DAILYPROGRAMMER_MANDELBROT_H


class Mandelbrot {
private:
    double width;
    double height;
    double maxRGB = 256;
    double minReal = -1.5;
    double maxReal = 0.7;
    double minImaginary = -1.0;
    double maxImaginary = 1.0;
    int maxIterations = 255;
    double MapToReal(int x);
    double MapToImaginary(int y);
    int CheckMandelbrot(double cr, double ci);
public:
    Mandelbrot(double width, double height);
    void Display();
};

#endif //DAILYPROGRAMMER_MANDELBROT_H
