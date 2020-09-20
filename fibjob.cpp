//
// Created by Lorne Zhang on 9/19/20.
//

#include "fibjob.h"
#include <mutex>
#include "threadpool.h"
using namespace std;

static mutex gmtx;
void showTask(int n) {
    gmtx.lock();
    printf("Adding fibonacci task %d\n", n);
    gmtx.unlock();
}

FibJob::FibJob(int n) : Job(){
    this->n = n;
}

FibJob::~FibJob() {
    gmtx.lock();
    printf("Fibonacci task %d being deleted\n", n);
    gmtx.unlock();
}

void FibJob::run(){
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

int FibJob::innerFib(int n) {
    if(n<=1) {
        return 1;
    }
    else {
        return innerFib(n-1) + innerFib(n-2);
    }
}

int FibJob::fibmain() {
    ThreadPool *tp = new ThreadPool(8);
    for (int i=0;i<30; ++i) {
        int rv = rand() % 30 + 9;
        showTask(rv);
        tp->addJob(new FibJob(rv));
    }
    tp->finish();
    tp->waitForCompletion();
    delete tp;
    printf("Done with all work!\n");
}