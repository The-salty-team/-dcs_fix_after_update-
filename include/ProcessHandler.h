
#ifndef PROCESSHANDLER_H
#define PROCESSHANDLER_H
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

class ProcessHandler : public Job
{
    public:

    void run()
    {
        while(!finished)
        {

            if(startproc)
            {
                ShellExecute(NULL,"open","C:/Program Files/Eagle Dynamics/DCS World/bin/DCS_updater.exe",NULL,NULL,SW_SHOWNORMAL);
                restartable=true;
            }

            else if(!startproc)
            {
                cout<<"gaygay";
                restartable=true;
            }
            sleep_for(seconds(5));
        }
        finished=true;
    }
    ProcessHandler(bool *gay):Job()
    {
        startproc=*gay;
    }
    bool startproc;
    bool _done;
};

#endif // PROCESSHANDLER_H
