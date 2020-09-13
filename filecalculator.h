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
    int GetFileSize(char *dirptr, char *filename);
    list<string> foldersToVisit;
    void AddFoldersToList(const char *dirptr);
public:
    FileCalculator();
    void Init();
    void Show();
    void CalculateRecursively(char *dirptr);
    void CalculateUsingThread(char *dirptr);
};

#endif //DAILYPROGRAMMER_FILECALCULATOR_H
