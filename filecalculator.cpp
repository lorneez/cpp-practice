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

#define NUM_THREADS 2

//struct dirent {
//    ino_t          d_ino;       /* inode number */
//    off_t          d_off;       /* offset to the next dirent */
//    unsigned short d_reclen;    /* length of this record */
//    unsigned char  d_type;      /* type of file; not supported
//                                   by all file system types */
//    char           d_name[256]; /* filename */
//};

using namespace std;

FileCalculator::FileCalculator() {
    Init();
}

void FileCalculator::Init() {
    totalsize = 0;
}

void FileCalculator::CalculateRecursively(char *dirptr) {
    struct dirent *entry = nullptr; // declares a pointer to dirent struct
    DIR *dp = nullptr; // declares a pointer for directory
    printf("Calculating at path: %s\n", dirptr);

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
                // cout << "THIS IS A FOLDER" << endl;
                string folder_path = dirptr;
                folder_path += entry->d_name;
                // cout << entry->d_name << endl;
                folder_path += "/";
                // cout << folder_path << endl;
                char *folderptr = new char[folder_path.length() + 1];
                strcpy(folderptr, folder_path.c_str());
                CalculateRecursively(folderptr);
                delete [] folderptr;
            }
    }

    // printf("\n");

    closedir(dp);
}

void FileCalculator::CalculateUsingThread(char *dirptr) {
    foldersToVisit.push_front(dirptr);
    pthread_t threads[NUM_THREADS];
    while(foldersToVisit.size() != 0) {
        int rc;
        int i;

        for( i = 0; i < NUM_THREADS; i++ ) {
            string currFolderStr = foldersToVisit.front().c_str();
            const char *currFolder = currFolderStr.c_str();
            cout << "CalculateUsingThread() : creating thread, " << i << endl;
            rc = pthread_create(&threads[i], NULL, AddFoldersToList, currFolder);
            if (rc) {
                cout << "Error:unable to create thread," << rc << endl;
                exit(-1);
            }
        }
    }
    pthread_exit(NULL);
}

void FileCalculator::AddFoldersToList(const char *dirptr) {
    struct dirent *entry = nullptr; // declares a pointer to dirent struct
    DIR *dp = nullptr; // declares a pointer for directory
    printf("Calculating at path: %s\n", dirptr);

    dp = opendir(dirptr);
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
                totalsize += (unsigned long int) GetFileSize(dirptr, entry->d_name);
                // cout << "THIS IS A FILE" << endl;
                cout << "totalsize: " << totalsize << endl;
            } else if (entry->d_type == 4) {
                // cout << "THIS IS A FOLDER" << endl;
                string folder_path = dirptr;
                folder_path += entry->d_name;
                // cout << entry->d_name << endl;
                folder_path += "/";


                // add to path
            }
    }
}

int FileCalculator::GetFileSize(char *dirptr, char *filename) {
    string filepath = dirptr;
    filepath += filename;
    // cout << filepath << endl;
    ifstream file( filepath, ios::binary | ios::ate);
    return file.tellg();
}

void FileCalculator::Show() {
    cout << totalsize << " Bytes!" << endl;
}