#include "smorse.h"
#include "decode.h"
#include "filecalculator.h"
#include "mandelbrot.h"
#include "fibjob.h"

void RunDecode() {
    Smorse s("lorne");
    s.ShowText();
    Decode d(".-.. --- .-. -. . .-..");
    d.ShowText();
}

void RunFileCalculator() {
    FileCalculator f;

    // f.CalculateRecursively("/Users/lorneez/");
    // 9370110329 Bytes!

    // f.CalculateUsingThreadLoop("/Users/lorneez/");
    // 16485208216 Bytes!

    f.CalculateUsingMultiThreading("/Users/lorneez/");
    // 29587857974 Bytes!

    f.Show();
}

void RunMandelbrot() {
    Mandelbrot m(100, 100);
    m.Display();
}

void RunFibThreadPool() {
    FibJob f(1);
    f.fibmain();
}

int main() {
    // RunDecode();
    // RunMandelbrot();
    // RunFileCalculator();
    RunFibThreadPool();
    return 0;
}