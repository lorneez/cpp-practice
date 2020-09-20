//
// Created by Lorne Zhang on 9/19/20.
//

#include "jobqueue.h"

JobQueue::JobQueue() {

}

JobQueue::~JobQueue() {

}

void JobQueue::addJob(Job* ptr) {
    if(!finished) {
        mtx.lock();
        jobs.push(ptr);
        mtx.unlock();
    }
}

Job* JobQueue::getJob() {
    Job* ptr;
    bool success = false;
    while(!success) { // loop until queue is full
        mtx.lock();
        if(jobs.size() == 0) {
            if(finished) {
                ptr = nullptr;
                success = true;
            }
        }
        else {
            ptr = jobs.front();
            jobs.pop();
            success = true;
        }
        mtx.unlock();
    }
    return ptr;
}

void JobQueue::finish() {
    mtx.lock();
    finished = true;
    mtx.unlock();
}

bool JobQueue::hasJobs() {
    return jobs.size() > 0;
}