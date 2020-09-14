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
    // f.CalculateRecursively("/Users/lorneez/");
    // 9370110329 Bytes!
    f.CalculateUsingThread("/Users/lorneez/");
    // 16485208216 Bytes!
    f.Show();
}

int main() {
    RunFileCalculator();
    return 0;
}