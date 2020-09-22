//
// Created by Lorne Zhang on 9/19/20.
//

#include "fibjob.h"
#include <mutex>
#include "threadpool.h"
#include <ctime>
#include <iostream>

using namespace std;

static mutex gmtx; // global mutex

void showTask(int n) { // print starting task
    gmtx.lock();
    printf("Adding fibonacci task %d\n", n);
    gmtx.unlock();
}

FibJob::FibJob(int n) : Job(){
    this->n = n;
}

FibJob::~FibJob() { // deconstructor, print delete task
    gmtx.lock();
    printf("Fibonacci task %d being deleted\n", n);
    gmtx.unlock();
}

void FibJob::run(){ // running fib task
    int val = innerFib(n);
    gmtx.lock();
    printf("Fib %d = %d\n",n, val);
    gmtx.unlock();
}

void FibJob::indicateTaken() {
    gmtx.lock();
    printf("Took fibonacci task %d\n", n);
    gmtx.unlock();
}

int FibJob::innerFib(int n) { // fib logic
    if(n<=1) {
        return 1;
    }
    else {
        return innerFib(n-1) + innerFib(n-2);
    }
}

int FibJob::fibmain(int n) {
    cout << "start: " << n << endl;
    unique_ptr<ThreadPool> poolPtr(new ThreadPool(n)); // new thread pool with 8 threads
    clock_t start = clock();
    for (int i=0;i<30; ++i) { // lets make 50 fib numbers
        // int rv = rand() % 20 + 3; // generate random number
        showTask(i);
        // unique_ptr<FibJob> jobPtr(new FibJob(i));
        poolPtr->addJob(new FibJob(i)); // give thread pool the task
    }
    poolPtr->finish(); // finish pool
    poolPtr->waitForCompletion(); // wait for pool to complete
    printf("Done with all work!\n");
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << n << " DURATION: " << duration << endl;
}