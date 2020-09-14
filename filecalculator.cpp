//
// Created by Lorne Zhang on 9/13/20.
//

#include "filecalculator.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <fstream>
#include <pthread.h>

#define NUM_THREADS 3

//struct dirent {
//    ino_t          d_ino;       /* inode number */
//    off_t          d_off;       /* offset to the next dirent */
//    unsigned short d_reclen;    /* length of this record */
//    unsigned char  d_type;      /* type of file; not supported
//                                   by all file system types */
//    char           d_name[256]; /* filename */
//};


typedef struct returnVal
{
    list<string> folders;
    int size;
    const char *currFolder;
    int thread;
};

using namespace std;

FileCalculator::FileCalculator() {
    Init();
}

void FileCalculator::Init() {
    totalsize = 0;
}

int GetFileSize(const char *dirptr, char *filename) {
    string filepath = dirptr;
    filepath += filename;
    ifstream file( filepath, ios::binary | ios::ate);

    // cout << filepath << endl;
    return file.tellg();
}

void FileCalculator::CalculateRecursively(char *dirptr) {
    struct dirent *entry = nullptr; // declares a pointer to dirent struct

    printf("Calculating at path: %s\n", dirptr);

    DIR *dp = nullptr; // declares a pointer for directory
    dp = opendir(dirptr);

    if (dp != nullptr) {
        while ((entry = readdir(dp)))
            if(entry->d_name[0] == '.'
            || strcmp(entry->d_name, "node_modules") == 0
            || strcmp(entry->d_name, "Library") == 0
            || strcmp(entry->d_name, "venv") == 0
            || strcmp(entry->d_name, "opt") == 0
            ) {
                continue;
            }
            else if(entry->d_type == 8) {
                totalsize +=  ( unsigned long int) GetFileSize(dirptr, entry->d_name);

                // cout << "THIS IS A FILE" << endl;
                cout << "totalsize: " << totalsize << endl;
            }
            else if(entry->d_type == 4) {
                string folder_path = dirptr;
                folder_path += entry->d_name;
                folder_path += "/";

                // cout << "THIS IS A FOLDER" << endl;
                // cout << entry->d_name << endl;
                // cout << folder_path << endl;

                char *folderptr = new char[folder_path.length() + 1];
                strcpy(folderptr, folder_path.c_str());

                CalculateRecursively(folderptr);

                delete [] folderptr;
            }
    }

    closedir(dp);
}

void *AddFoldersToList(void *arg) {
    returnVal *tdata=(returnVal *)arg;
    tdata -> size = 0;

    struct dirent *entry = nullptr; // declares a pointer to dirent struct
    const char* const dirptr = reinterpret_cast<const char* const>(tdata -> currFolder);

    DIR *dp = nullptr; // declares a pointer for directory
    dp = opendir(dirptr);

    // printf("Thread %d in use\n", tdata->thread);
    //cout << "THREAD " << tdata->thread << " in use" << endl;

    if (dp != nullptr) {
        while ((entry = readdir(dp)))
            if (entry->d_name[0] == '.'
                || strcmp(entry->d_name, "node_modules") == 0
                || strcmp(entry->d_name, "Library") == 0
                || strcmp(entry->d_name, "venv") == 0
                || strcmp(entry->d_name, "opt") == 0
                    ) {
                continue;
            } else if (entry->d_type == 8) {
                tdata -> size += (unsigned long int) GetFileSize(dirptr, entry->d_name);

                // cout << "THIS IS A FILE" << endl;
                // cout << "totalsize: " << tdata -> size << endl;
            } else if (entry->d_type == 4) {
                string folder_path = dirptr;
                folder_path += entry->d_name;
                folder_path += "/";

                tdata -> folders.push_front(folder_path);

                // cout << "THIS IS A FOLDER" << endl;
                // cout << entry->d_name << endl;
            }
    }
    //cout << "Exiting THREAD " << tdata->thread << endl;
    pthread_exit(NULL);
}

void FileCalculator::CalculateUsingThread(char *dirptr) {
    string dir(dirptr);
    foldersToVisit.push_front(dir);

    pthread_t threads[NUM_THREADS];

    while(foldersToVisit.size() != 0) {
        int i;
        for( i = 0; i < NUM_THREADS; i++ ) {
            string currFolderStr = foldersToVisit.front().c_str();
            const char *currFolder = currFolderStr.c_str();

            returnVal tdata;
            tdata.thread = i;
            tdata.currFolder = currFolder;

            pthread_create(&threads[i], NULL, AddFoldersToList, (void *)&tdata);
            pthread_join(threads[i], NULL);

            totalsize += tdata.size;

            cout << totalsize << endl;
            // printf("TOTAL SIZE: %\n", totalsize);

            foldersToVisit.pop_front();
            foldersToVisit.merge(tdata.folders);
        }
    }
}


void FileCalculator::Show() {
    cout << totalsize << " Bytes!" << endl;
}