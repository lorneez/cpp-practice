//
// Created by Lorne Zhang on 9/19/20.
//

#ifndef DAILYPROGRAMMER_JOB_H
#define DAILYPROGRAMMER_JOB_H


class Job {
public:
    Job() {}
    ~Job() = default; // destructor
    // virtual functions are overridden in runtime by a derived class, a class that extends it
    virtual void run()=0; // run the Job
    virtual void indicateTaken()=0; // indicate if thread has taken Job
};


#endif //DAILYPROGRAMMER_JOB_H
