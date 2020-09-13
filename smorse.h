//
// Created by Lorne Zhang on 9/12/20.
//

#ifndef DAILYPROGRAMMER_SMORSE_H
#define DAILYPROGRAMMER_SMORSE_H
#include <string>
#include <map>

using namespace std;

class Smorse {
private:
    string input;
    string converted;
    map<char, string> morseTable;

public:
    Smorse(string input);
    void InitTable();
    void Convert();
    void ShowText();
};

#endif //DAILYPROGRAMMER_SMORSE_H
