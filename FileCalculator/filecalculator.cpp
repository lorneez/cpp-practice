//
// Created by Lorne Zhang on 9/13/20.
//

#include "filecalculator.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <dirent.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <atomic>
#define NUM_THREADS 2

/**
 * Struct for the non-parallel thread method
 */
struct returnVal
{
    list<string> folders;
    int size;
    const char *currFolder;
    int thread;
};

using namespace std;

/**
 * Constructor
 */
FileCalculator::FileCalculator() {
    Init();
}

/**
 * Initialize totalsize to 0. Not much else is needed
 */
void FileCalculator::Init() {
    totalsize = 0;
}

/**
 * Obtains the size of the file with ifstream, a class to operate on files.
 * @param dirptr
 * @param filename
 * @return size of file in bytes
 */
int GetFileSize(const char *dirptr, char *filename) {
    string filepath = dirptr;
    filepath += filename;

    // initialization constructor
    // binary to prevent translation of new line characters
    // ate directly seeks the end of the file
    ifstream file( filepath, ios::binary | ios::ate);

    // obtains difference between current get pointer and start pointer
    return file.tellg();
}

/**
 * METHOD 1: RECURSION
 * Obtains total size of files with recursive calls.
 * @param dirptr
 */
void FileCalculator::CalculateRecursively(const char *dirptr) {
    // declares a pointer to dirent struct, to interact with the file
    struct dirent *entry = nullptr;

    printf("Calculating at path: %s\n", dirptr);

    // declares a pointer for directory
    DIR *dp = nullptr;
    dp = opendir(dirptr);

    if (dp != nullptr) {
        while ((entry = readdir(dp)))
            // skip certain files that are too large
            if(entry->d_name[0] == '.'
               || strcmp(entry->d_name, "node_modules") == 0
               || strcmp(entry->d_name, "Library") == 0
               || strcmp(entry->d_name, "venv") == 0
               || strcmp(entry->d_name, "opt") == 0
                    ) {
                continue;
            }
            else if(entry->d_type == 8) {
                // Found file
                totalsize +=  ( unsigned long int) GetFileSize(dirptr, entry->d_name);
                cout << "totalsize: " << totalsize << endl;
            }
            else if(entry->d_type == 4) {
                // Found folder

                string folder_path = dirptr;
                folder_path += entry->d_name;
                folder_path += "/";
                char *folderptr = new char[folder_path.length() + 1]; // declare new because we have no idea how many folder pointers we will need
                strcpy(folderptr, folder_path.c_str());
                CalculateRecursively(folderptr);
                delete [] folderptr; // free the current folder pointer because we no longer need it
            }
    }
    closedir(dp);
}

/**
 * Adds folders to the returnVal struct. This method is a job for a thread
 * @param arg
 * @return
 */
void *AddFoldersToList(void *arg) {
    returnVal *tdata = (returnVal *) arg;
    tdata -> size = 0;

    struct dirent *entry = nullptr;
    // This is a pointer that i cannot modify to a char that i cannot modify
    // const pointer -> const char
    const char* const dirptr = reinterpret_cast<const char* const>(tdata -> currFolder);

    DIR *dp = nullptr;
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
                // add size to tdata
                tdata -> size += (unsigned long int) GetFileSize(dirptr, entry->d_name);
            } else if (entry->d_type == 4) {
                string folder_path = dirptr;
                folder_path += entry->d_name;
                folder_path += "/";
                tdata -> folders.push_front(folder_path);
            }
    }
    pthread_exit(NULL);
}

/**
 * METHOD 2: NON-PARALLEL THREADS
 * Funny method that uses threads in a loop
 * @param dirptr
 */
void FileCalculator::CalculateUsingThreadLoop(const char *dirptr) {
    string dir(dirptr);
    foldersToVisit.push_front(dir);
    pthread_t threads[NUM_THREADS];

    // keep iterating when there are still folders to visit
    while(!foldersToVisit.empty()) {
        // iterate through all threads to "assign them" a new job
        for( int i = 0; i < NUM_THREADS; i++ ) {
            // get first folder on list
            string currFolderStr = foldersToVisit.front().c_str();
            const char *currFolder = currFolderStr.c_str();

            // initalize a returnVal struct for each thread
            returnVal tdata;
            tdata.thread = i;
            tdata.currFolder = currFolder;

            // create thread, give it AddFoldersToList job, and the returnVal data structure
            pthread_create(&threads[i], NULL, AddFoldersToList, (void *)&tdata);
            // join thread
            pthread_join(threads[i], NULL);

            // add thread's data to the entire data size
            totalsize += tdata.size;

            cout << totalsize << endl;

            // remove the front folder, add the new folders
            foldersToVisit.pop_front();
            foldersToVisit.merge(tdata.folders);
        }
    }
}

/**
 * Display current total size of files found
 */
void FileCalculator::Show() {
    cout << totalsize << " Bytes!" << endl;
}

/**
 * METHOD 3: MULTITHREADING
 * @param dirptr
 */
void FileCalculator::CalculateUsingMultiThreading(const char *dirptr) {
    string folder(dirptr);
    foldersToVisit.push_front(folder);
    // not sure if this loop is correct. keep on checking if the folder is not empty.

    // create thread 1
    thread t1(&FileCalculator::MTAccessList, this, 1);

    // create thread 2
    thread t2(&FileCalculator::MTAccessList, this, 2);

    // join threads
    t1.join();
    t2.join();
}


/**
 * Multithreading job
 */
void FileCalculator::MTAccessList(int threadNum) {
    printf("Thread %d has started!\n", threadNum);
    // infinite loop
    while(true)
    {
        {
            // lock
            mtx.lock();
            printf("Thread %d obtains lock!\n", threadNum);

            // check if list is empty
            if(!foldersToVisit.empty()) {

                // update atomic counter: thread is active
                // cout << "Thread is active" << endl;
                MTCounter++;

                // get and remove next folder
                // get const char*
                const char *nextFolderCPtr = foldersToVisit.front().c_str();

                // convert to string
                string nextFolderStr(nextFolderCPtr);

                // delete first list element
                foldersToVisit.pop_front();

                // unlock
                mtx.unlock();

                // create char*
                char * nextFolder = new char[nextFolderStr.size() + 1];
                std::copy(nextFolderStr.begin(), nextFolderStr.end(), nextFolder);
                nextFolder[nextFolderStr.size()] = '\0'; // remove terminating 0

                // find folders and files in next folder
                MTFindFoldersAndFiles(nextFolder);

                // delete nextFolder pointer
                delete[] nextFolder;

                // update atomic counter: thread deposited folders
                // cout << "Thread deposited folder" << endl;
                MTCounter--;
            }

                // if list empty, break;
            else {
                mtx.unlock();
                if(MTCounter == 0) {
                    printf("Thread %d has exited!\n", threadNum);
                    break;
                }
            }
        }
    }
}

void FileCalculator::MTFindFoldersAndFiles(char *dir) {
    struct dirent *entry = nullptr;
    DIR *dp = nullptr;
    dp = opendir(dir);

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
                // protect access to totalsize
                mtx.lock();
                totalsize += (unsigned long int) GetFileSize(dir, entry->d_name);
                mtx.unlock();
            } else if (entry->d_type == 4) {
                string folder_path = dir;
                folder_path += entry->d_name;
                folder_path += "/";
                char *folderptr = new char[folder_path.length() + 1];
                strcpy(folderptr, folder_path.c_str());
                // protect access to foldersToVisit
                mtx.lock();
                foldersToVisit.push_front(folderptr);
                mtx.unlock();
                delete[] folderptr;

            }
    }
    closedir(dp);
}

// 96168559994
// 96168560010