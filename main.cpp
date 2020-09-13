#include "smorse.h"
#include "decode.h"
#include "filecalculator.h"

void RunDecode() {
    Smorse s("lorne");
    s.ShowText();
    Decode d(".-.. --- .-. -. . .-..");
    d.ShowText();
}

void RunFileCalculator() {
    FileCalculator f;
    f.CalculateRecursively("/Users/lorneez/");
    f.CalculateUsingThread("/Users/lorneez/");
    f.Show();
}

int main() {
    RunFileCalculator();
    return 0;
}