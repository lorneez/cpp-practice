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
public:
    FileCalculator();
    void Init();
    void Show();
    void CalculateRecursively(const char *dirptr);
    void CalculateUsingThreadLoop(const char *dirptr);
    void CalculateUsingMultiThreading(const char *dirptr);
private:
    unsigned long int totalsize;
    list<string> foldersToVisit;
    mutex mtx;
    atomic<int> MTCounter;
    void MTAccessList(int threadNum);
    void MTFindFoldersAndFiles(char *dir);
};

#endif //DAILYPROGRAMMER_FILECALCULATOR_H