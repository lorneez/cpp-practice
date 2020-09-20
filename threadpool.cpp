//
// Created by Lorne Zhang on 9/19/20.
//

#include "threadpool.h"
#include <iostream>

using namespace std;


static void* getWork(void* param) {
    Job* ptr = 0; // new job
    JobQueue* jqptr = (JobQueue*)param; // job queue
    while(ptr = jqptr->getJob()) { // while job queue has jobs get a job
        ptr->indicateTaken(); // this job is taken
        ptr->run(); // run this job
        delete ptr;
    }
    return 0;
}

ThreadPool::ThreadPool(int numThreads) {
    this->numThreads = numThreads;
    t = new thread[numThreads];
    for(int i=0; i<numThreads; i++) {
        t[i] = thread(getWork, &jobQueue);
    }
}

ThreadPool::~ThreadPool() {
    jobQueue.finish(); // job queue done
    for(int i=0; i<numThreads; i++) { // join all threads
        t[i].join();
    }
    delete [] t; // delete threads
}

void ThreadPool::finish() {
    jobQueue.finish();
}

bool ThreadPool::hasJobs() {
    return jobQueue.hasJobs();
}

void ThreadPool::addJob(Job *ptr) {
    jobQueue.addJob(ptr);
}

void ThreadPool::waitForCompletion() {
    while(jobQueue.hasJobs()) {

    }
}