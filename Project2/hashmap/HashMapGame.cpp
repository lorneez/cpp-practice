//
// Created by Lorne Zhang on 11/27/20.
//

#include "HashMapGame.h"
#include <iostream>

HashMapGame::HashMapGame() {
    this->isFinished = false;
}

void HashMapGame::checkContainsAll() {
    if(map.size() == 10) {
        std::cout << "Wow, map has all 10 numbers!" << std::endl;
        auto it_looper = map.begin();
        std::cout << "Current Contents:" << std::endl;
        while(it_looper != map.end()) {
            std::cout << it_looper->first << " : " << it_looper->second << std::endl;
            it_looper++;
        }
    }

}

void HashMapGame::checkFinished() {
    it = map.begin();
    while(it != map.end()) {
        if(it->second == 10) {
            this->isFinished = true;
            std::cout << "Finished: " << it->first << " has 10 copies!" << std::endl;
            auto it_looper = map.begin();
            std::cout << "Final Contents:" << std::endl;
            while(it_looper != map.end()) {
                std::cout << it_looper->first << " : " << it_looper->second << std::endl;
                it_looper++;
            }
            break;
        }
        it++;
    }

}

void HashMapGame::checkSum(std::map<int, int> &map) {
    auto it = map.begin();
    int sum = 0;
    while(it != map.end()) {
        sum += it->second;
        it++;
    }
    if(sum >= 100) {
        std::cout << "Dang... map sum has reached: " << sum << std::endl;
    }
}

void HashMapGame::run() {
    while(!isFinished) {
        int next = random() % 10;
        it = map.find(next);

        if(it == map.end()) {
            map[next] = 1;
        }
        else {
            map[next]++;
        }

        checkMember(&HashMapGame::checkContainsAll);
        checkStatic(map, checkSum);
        checkMember(&HashMapGame::checkFinished);
    }
}

void HashMapGame::checkMember(void (HashMapGame::*func)()) {
    (this->*func)();
}

void HashMapGame::checkStatic(std::map<int, int> &map,void (*func)(std::map<int, int> &map)) {
    (*func)(map);
}