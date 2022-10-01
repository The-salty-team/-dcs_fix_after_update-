#ifndef WORKER_H
#define WORKER_H

#include <condition_variable>
#include <mutex>
#include <thread>

#include "job.h"

using namespace std;

class worker
{
    public:
        Job *_job;
        bool running;
        bool working;
        bool restart;
        bool restarting;
        void run();
        void work();
        worker();
        virtual ~worker();
        condition_variable _cv;
        unique_lock<mutex> _lock;
    protected:

    private:
        mutex _mutex;

        thread *_thread;


};

#endif // WORKER_H
