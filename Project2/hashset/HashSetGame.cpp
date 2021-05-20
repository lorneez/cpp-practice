//
// Created by Lorne Zhang on 11/27/20.
//

#include "HashSetGame.h"
#include <iostream>

HashSetGame::HashSetGame() {
    this->set = std::unordered_set<int>();
    for(int i=0; i<10; i++) {
        set.insert(i);
    }
}

void HashSetGame::run() {
    while(set.size() != 1) {
        for(auto ele : set) {
            std::cout << ele;
        }
        std::cout << std::endl;

        int modify_choice = rand() % 3 + 1;
        switch (modify_choice) {
            case 1:
                modify(&HashSetGame::add);
                break;
            case 2:
                modify(&HashSetGame::subtract);
                break;
            case 3:
                modify(&HashSetGame::mod);
                break;
            default:
                continue;
        }
    }
}

void HashSetGame::add() {
    int index = rand() % set.size();
    int constant = rand() % 10;
    auto it = set.begin();
    std::advance(it, index);
    int toModify = *it;
    set.erase(it);
    int next = (toModify + constant)%10;
    if(next < 0) {
        next = -next;
    }
    std::cout << "add: removed: " << toModify << ", added: " << next << std::endl;
    set.insert(next);
}

void HashSetGame::subtract() {
    int index = rand() % set.size();
    int constant = rand() % 10;
    auto it = set.begin();
    std::advance(it, index);
    int toModify = *it;
    set.erase(it);
    int next = (toModify - constant)%10;
    if(next < 0) {
        next = -next;
    }
    std::cout << "sub: removed: " << toModify << ", added: " << next << std::endl;
    set.insert(next);
}

void HashSetGame::mod() {
    int index = rand() % set.size();
    int constant = rand() % 9 + 1;
    auto it = set.begin();
    std::advance(it, index);
    int toModify = *it;
    set.erase(it);
    int next = toModify%constant;
    if(next < 0) {
        next = -next;
    }
    std::cout << "mod: removed: " << toModify << ", added: " << next << std::endl;
    set.insert(next);
}

void HashSetGame::modify(void (HashSetGame::*func)()) {
    (this->*func)();
}