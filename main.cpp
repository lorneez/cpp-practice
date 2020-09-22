#include "smorse.h"
#include "decode.h"
#include "filecalculator.h"
#include "mandelbrot.h"
#include "fibjob.h"
#include "imageconverter.h"

/**
 * Test for decode smorse
 */
void RunDecode() {
    Smorse s("lorne");
    s.ShowText();
    Decode d(".-.. --- .-. -. . .-..");
    d.ShowText();
}

/**
 * Test for file calculator
 */
void RunFileCalculator() {
    FileCalculator f;

    // f.CalculateRecursively("/Users/lorneez/");
    // 9370110329 Bytes!

    // f.CalculateUsingThreadLoop("/Users/lorneez/");
    // 16485208216 Bytes!

    // f.CalculateUsingMultiThreading("/Users/lorneez/");
    // 29587857974 Bytes!

    f.Show();
}

/**
 * Test for mandelbrot
 */
void RunMandelbrot() {
    Mandelbrot m(100, 100);
    m.Display();
}

/**
 * Test for thread pool
 */
void RunFibThreadPool() {
    FibJob f(1);
    for(int i=1; i<20; i++) {
        f.fibmain(i);
    }
}

/**
 * Test for image converter
 */
void RunImageConverted() {
    ImageConverter i("../Cyan.png", "../test.txt");
    i.run();
}

int main() {
    // RunDecode();
    // RunMandelbrot();
    // RunFileCalculator();
    // RunFibThreadPool();
    RunImageConverted();
    return 0;
}