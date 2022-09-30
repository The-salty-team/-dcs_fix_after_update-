#include "jobMan.h"

jobMan::jobMan()
{
    _instance = this;
}
jobMan::add_job(job *_job)
{
    _mutex.lock();
    Vjobs.push_back(_job);
    _mutex.unlock();
    jobMan::add_to_queue();
}

jobMan::job_finished()
{
    jobMan::add_to_queue();
}
jobMan::new_worker()
{
    _worker.push_back(new worker());
}
jobMan::add_to_queue()
{
    _mutex.lock();
    if (Vjobs.size()==0)
    {
        _mutex.unlock;
        return;
    }
    _workers.push_back(new worker());
    for (unsigned int i=0;i<_workers.size();++i)
    {
        worker *w=_workers[i];
        if(!w->working)
        {
            job *new_job=Vjobs[0];
            Vjobs[0]=Vjobs[Vjobs.size()-1];
            Vjobs.pop_back();
            w->job = new_job;
            w->work;
            _mutex.unlock();
            return;
        }
    }
    _mutex.unlock();
}
jobMan::jobMan *get_singleton();
{
    return _instance;
}
jobMan::~jobMan()
{
    //dtor
}
