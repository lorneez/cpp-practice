#include "smorse.h"
#include "decode.h"
#include "filecalculator.h"
#include "mandelbrot.h"


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
    Mandelbrot m(5000, 5000);
    m.Display();
}

int main() {
    // RunMandelbrot();
    RunFileCalculator();
    return 0;
}