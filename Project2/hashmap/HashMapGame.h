//
// Created by Lorne Zhang on 11/27/20.
//

#ifndef DAILYPROGRAMMER_HASHMAPGAME_H
#define DAILYPROGRAMMER_HASHMAPGAME_H
#include <map>

class HashMapGame {
public:
    HashMapGame();
    void run();

private:
    std::map<int, int> map;
    std::map<int, int>::iterator it;
    void checkMember(void (HashMapGame::*func)());
    void checkStatic(std::map<int, int> &map,void (*func)(std::map<int, int> &));
    void checkContainsAll();
    void checkFinished();
    static void checkSum(std::map<int, int> &map);
    bool isFinished;
};


#endif //DAILYPROGRAMMER_HASHMAPGAME_H
