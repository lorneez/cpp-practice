//
// Created by Lorne Zhang on 11/27/20.
//

#ifndef DAILYPROGRAMMER_HASHSETGAME_H
#define DAILYPROGRAMMER_HASHSETGAME_H
#include <unordered_set>

class HashSetGame {
public:
    HashSetGame();
    void run();
private:
    void modify(void (HashSetGame::*func)()); // modifies an element in the set
    void add(); // add a random number and mod 10
    void subtract(); // add a random number and mod 10
    void mod(); // mod a number between 0-9
    std::unordered_set<int> set; // always contains elements 0-9
};


#endif //DAILYPROGRAMMER_HASHSETGAME_H
