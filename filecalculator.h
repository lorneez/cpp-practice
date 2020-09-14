//
// Created by Lorne Zhang on 9/13/20.
//

#ifndef DAILYPROGRAMMER_FILECALCULATOR_H
#define DAILYPROGRAMMER_FILECALCULATOR_H
#include <string>
#include <list>

using namespace std;

class FileCalculator {
private:
    unsigned long int totalsize;
public:
    FileCalculator();
    void Init();
    void Show();
    void CalculateRecursively(char *dirptr);
    void CalculateUsingThread(char *dirptr);
    list<string> foldersToVisit;
};

#endif //DAILYPROGRAMMER_FILECALCULATOR_H
