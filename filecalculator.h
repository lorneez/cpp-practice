//
// Created by Lorne Zhang on 9/13/20.
//

#ifndef DAILYPROGRAMMER_FILECALCULATOR_H
#define DAILYPROGRAMMER_FILECALCULATOR_H
#include <string>
#include <list>
#include <mutex>

using namespace std;

class FileCalculator {
private:
    unsigned long int totalsize;
    list<string> foldersToVisit;
    mutex mtx;
    atomic<int> MTCounter;
    void MTAccessList();
    void MTFindFoldersAndFiles(char *dir);
public:
    FileCalculator();
    void Init();
    void Show();
    void CalculateRecursively(char *dirptr);
    void CalculateUsingThreadLoop(char *dirptr);
    void CalculateUsingMultiThreading(char *dirptr);
};

#endif //DAILYPROGRAMMER_FILECALCULATOR_H