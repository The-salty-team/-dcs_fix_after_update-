#ifndef JOB_H
#define JOB_H
#include "windows.h"
#include "tlhelp32.h"

class job
{
    public:
        bool finished;
        virtual void run();
        job();
        virtual ~job();

    protected:

    private:
};

#endif // JOB_H
