//
// Created by Lorne Zhang on 9/12/20.
//

#include "decode.h"
#include <iostream>

using namespace std;

Decode::Decode(string input){
    this -> input = input;
    InitTable();
    Convert();
}

void Decode::InitTable() {
    string all = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --..";
    string delimiter = " ";
    size_t pos = 0; // unsized long
    string token; // current word
    char c = 'a'; // key for map
    while ((pos = all.find(delimiter)) != string::npos) { // npos is the greatest possible val for size_t. signifies end of string
        token = all.substr(0, pos); // pos is the first index of delimiter. substr isolates first part
        morseTable[token] = c; // set into char
        c ++;
        all.erase(0, pos + delimiter.length());
    }
}

void Decode::Convert() {
    string all = input;
    string delimiter = " ";
    size_t pos = 0; // unsized long
    string token; // current word
    while ((pos = all.find(delimiter)) != string::npos) { // npos is the greatest possible val for size_t. signifies end of string
        token = all.substr(0, pos); // pos is the first index of delimiter. substr isolates first part
        converted = converted + morseTable[token];
        all.erase(0, pos + delimiter.length());
    }
}

void Decode::ShowText() {
    cout << converted << endl;
}