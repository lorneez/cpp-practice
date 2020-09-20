//
// Created by Lorne Zhang on 9/19/20.
//

#ifndef DAILYPROGRAMMER_THREADPOOL_H
#define DAILYPROGRAMMER_THREADPOOL_H

#include <pthread.h>
#include "jobqueue.h"

using namespace std;

class ThreadPool {
public:
    ThreadPool(int numThreads);
    ~ThreadPool();
    void addJob(Job* ptr);
    void finish();
    bool hasJobs();
    void waitForCompletion();

private:
    pthread_t* t;
    int numThreads;
    JobQueue jobQueue;
};


#endif //DAILYPROGRAMMER_THREADPOOL_H
