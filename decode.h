//
// Created by Lorne Zhang on 9/12/20.
//

#ifndef DAILYPROGRAMMER_DECODE_H
#define DAILYPROGRAMMER_DECODE_H
#include <string>
#include <list>
#include <map>

using namespace std;

class Decode {
private:
    string input;
    list<string> possibleConversions;
    string converted;
    map<string, char> morseTable;

public:
    Decode(string input);
    void InitTable();
    void Convert();
    void ShowText();
};

#endif //DAILYPROGRAMMER_DECODE_H
