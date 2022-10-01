#include "jobMan.h"
jobMan *jobMan::_instance=nullptr;

jobMan::jobMan()
{
    _instance = this;
}
void jobMan::add_job(Job *_job)
{
    _mutex.lock();
    Vjobs.push_back(_job);
    _mutex.unlock();
    jobMan::add_to_queue();
}

void jobMan::job_finished()
{
    jobMan::add_to_queue();
}
void jobMan::new_worker()
{
    _workers.push_back(new worker());
}

void jobMan::restart_worker()
{
    ////////////////////////////////////////////////////FIX THIS SHIT//////////////////////////////////////////////////////////////////////////
    /*/
    Saved_Job->finished=false;
    _mutex.lock();
    for (unsigned int i=0;i<_workers.size();++i)
    {
        worker *w=_workers[i];
        if(!w->working || w->_job->restartable)
        {

            Vjobs.push_back(&Saved_Job);
            Job *re_job=Vjobs[0];
            Vjobs[0]=Vjobs[Vjobs.size()-1];
            w->_job = re_job;
            w->restarting=true;

            w->work();
            Vjobs.pop_back();
            _mutex.unlock();
            return;
        }
    }
    _mutex.unlock();
    Saved_Job.restartable=false;
    Saved_Job.finished=false;
    add_job(&Saved_Job,true);
    /*/
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void jobMan::add_to_queue()
{
    _mutex.lock();
    if (Vjobs.size()==0)
    {
        _mutex.unlock();
        return;
    }

    for (unsigned int i=0;i<_workers.size();++i)
    {
        worker *w=_workers[i];
        if(!w->working)
        {
            Job *new_job=Vjobs[0];
            Vjobs[0]=Vjobs[Vjobs.size()-1];
            w->_job = new_job;
            w->work();
            if(w->_job->restartable) Saved_Job=*new_job;

            Vjobs.pop_back();
            _mutex.unlock();
            return;
        }
    }
    _mutex.unlock();
}

jobMan *jobMan::get_singleton()
{
    return _instance;
}
jobMan::~jobMan()
{
    _mutex.lock();
    Vjobs.clear();

    _mutex.unlock();
    for (int i=0;i<_workers.size();++i)
    {
        delete _workers[i];
    }
}
