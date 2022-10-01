#ifndef JOBMAN_H
#define JOBMAN_H

#include "job.h"
#include "worker.h"
#include <mutex>
#include <thread>
#include <vector>
class jobMan
{
    public:
        void add_job(Job *_job);
        void add_job(Job *_job,bool restart);
        void job_finished();
        void add_to_queue();
        void add_to_queue(bool restart);
        void restart_worker();
        static jobMan *get_singleton();
        jobMan();
        virtual ~jobMan();
        void new_worker();
        Job Saved_Job;
    protected:

    private:
        std::vector<Job *> Vjobs;
        std::vector<worker *> _workers;
        std::mutex _mutex;
        static jobMan* _instance;
};

#endif // JOBMAN_H
