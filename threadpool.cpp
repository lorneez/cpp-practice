//
// Created by Lorne Zhang on 9/19/20.
//

#include "threadpool.h"

using namespace std;


static void* getWork(void* param) {
    Job* ptr = nullptr; // new job
    auto* jqptr = (JobQueue*)param; // job queue
    while(ptr = jqptr->getJob()) { // while job queue has jobs get a job
        ptr->indicateTaken(); // this job is taken
        ptr->run(); // run this job
        delete ptr;
    }
    return nullptr;
}

ThreadPool::ThreadPool(int numThreads) {
    this->numThreads = numThreads;
    t = new pthread_t[numThreads];
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

void ThreadPool::addJob(Job *ptr) {
    jobQueue.addJob(ptr);
}

void ThreadPool::waitForCompletion() {
    while(jobQueue.hasJobs()) {

    }
}