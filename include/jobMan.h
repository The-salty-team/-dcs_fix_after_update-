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
        void add_job(job *_job);
        void job_finished();
        void add_to_queue();
        static jobMan *get_singleton();
        jobMan();
        virtual ~jobMan();
        void new_worker();

    protected:

    private:
        std::vector<job *> Vjobs;
        std::vector<worker *> _workers;
        std::mutex _mutex;
        static jobMan* _instance;
};

#endif // JOBMAN_H
