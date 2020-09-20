//
// Created by Lorne Zhang on 9/19/20.
//

#ifndef DAILYPROGRAMMER_FIBJOB_H
#define DAILYPROGRAMMER_FIBJOB_H

#include "job.h"

class FibJob : public Job{ // fib job extends job
public:
    FibJob(int n);
    ~FibJob();
    virtual void run();
    virtual void indicateTaken();
    int fibmain();
private:
    int innerFib(int n);
    int n;
};


#endif //DAILYPROGRAMMER_FIBJOB_H
