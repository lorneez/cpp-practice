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
    mtx.lock();
    if(finished && jobs.size() == 0) {
        ptr = 0;
        mtx.unlock();
    }
    else {
        if(jobs.size() == 0) { // check if the queue is empty
            mtx.unlock(); // unlock
            while(jobs.size() == 0) { // loop until queue is full
                if(finished) {
                    return 0;
                }
            }
            mtx.lock(); // lock
        }
        // get job
        ptr = jobs.front();
        jobs.pop();
        mtx.unlock();
    };
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