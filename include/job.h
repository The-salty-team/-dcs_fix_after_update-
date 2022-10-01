#ifndef JOB_H
#define JOB_H

#include "windows.h"
#include "tlhelp32.h"

class Job
{
    public:

        virtual void run();
        Job();
        virtual ~Job();
        bool finished;
        bool restartable;

};

#endif // JOB_H
