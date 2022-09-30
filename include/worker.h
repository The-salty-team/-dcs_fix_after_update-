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
        job *_job;
        bool running;
        bool working;
        void run();
        void work();
        worker();
        virtual ~worker();

    protected:

    private:
        mutex _mutex;
        conditional_variable _cv;
        unique_lock<_mutex> _lock;
        thread *_thread;


};

#endif // WORKER_H
