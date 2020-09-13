//
// Created by Lorne Zhang on 9/12/20.
//

#include <string>
#include <iostream>
#include "smorse.h"

using namespace std;

Smorse::Smorse(string input) {
    this -> input = input;
    InitTable();
    Convert();
}

void Smorse::InitTable() {
    string all = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --..";
    string delimiter = " ";
    size_t pos = 0; // unsized long
    string token; // current word
    char c = 'a'; // key for map
    while ((pos = all.find(delimiter)) != string::npos) { // npos is the greatest possible val for size_t. signifies end of string
        token = all.substr(0, pos); // pos is the first index of delimiter. substr isolates first part
        morseTable[c] = token; // set into char
        c ++;
        all.erase(0, pos + delimiter.length());
    }
}

void Smorse::Convert() {
    for(char const &c : input) {
        converted = converted + morseTable[c] + " ";
    }
}

void Smorse::ShowText() {
    cout << converted << endl;
}