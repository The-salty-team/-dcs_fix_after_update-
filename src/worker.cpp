#include "worker.h"
#include "jobMan.h"
worker::worker()
{
    running=true;
    _lock=unique_lock<mutex>(_mutex);
    working=false;
    _job=nullptr;
    _thread=new thread(&worker::run,this);
}
void worker::run()
{
    while(running)
    {
        if(job) _job->run();

        working =false;
        _job = nullptr;

        jobMan::get_singleton()->job_finished();
        if (!job)
        {
            _cv.wait(_lock);
        }
    }
}

void worker::work()
{
    working=true;
    _cv.notify_one();
}
worker::~worker()
{
    running=false;
    _cv.notify_one();
    _thread->join();
    delete _thread;
}
