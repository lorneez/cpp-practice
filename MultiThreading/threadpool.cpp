//
// Created by Lorne Zhang on 9/19/20.
//

#include "threadpool.h"

using namespace std;


static void* getWork(void* param) {
    Job* ptr = nullptr; // new job  -> unique pointer
    auto* jqptr = (JobQueue*)param; // job queue
    while(ptr = jqptr->getJob()) { // while job queue has jobs get a job -> get job returns unique pointer
        ptr->indicateTaken(); // this job is taken
        ptr->run(); // run this job
        delete ptr; // no need to delete unique pointer
    }
    return nullptr;
}

ThreadPool::ThreadPool(int numThreads) {
    this->numThreads = numThreads;
    t = new pthread_t[numThreads]; // vector of threads
    for(int i=0; i<numThreads; i++) {
        pthread_create(&(t[i]), 0, getWork, &jobQueue);
    }
}

ThreadPool::~ThreadPool() {
    jobQueue.finish(); // job queue done
    for(int i=0; i<numThreads; i++) { // join all threads
        pthread_join(t[i], 0);
    }
    delete [] t; // delete threads
}

void ThreadPool::finish() {
    jobQueue.finish();
}

bool ThreadPool::hasJobs() {
    return jobQueue.hasJobs();
}

void ThreadPool::addJob(Job* ptr) {
    jobQueue.addJob(ptr);
}

void ThreadPool::waitForCompletion() {
    while(jobQueue.hasJobs()) {

    }
}