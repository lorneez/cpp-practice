//
// Created by Lorne Zhang on 9/19/20.
//

#ifndef DAILYPROGRAMMER_JOBQUEUE_H
#define DAILYPROGRAMMER_JOBQUEUE_H
#include <queue>
#include <mutex>
#include "job.h"

using namespace std;

class JobQueue {
public:
    JobQueue();
    ~JobQueue();
    Job* getJob();
    void addJob(Job* ptr);
    void finish();
    bool hasJobs();
private:
    queue<Job*> jobs; // a queue of Job unique pointers
    bool finished;
    mutex mtx;
};


#endif //DAILYPROGRAMMER_JOBQUEUE_H
