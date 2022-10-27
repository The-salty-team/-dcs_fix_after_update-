
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

            if(*startproc)
            {
                cout<<"Starting Updater"<<endl;
                ShellExecute(NULL,"open","C:/Program Files/Eagle Dynamics/DCS World/bin/DCS_updater.exe",NULL,NULL,SW_SHOWNORMAL);
                finished=true;
            }

            else if(!*startproc)
            {
                LPDWORD exit;
                TerminateProcess(*Dcs,0);
                cout<<"Terminating process: "<<*Dcs<<endl;
                finished=true;
            }
            sleep_for(seconds(5));
        }
        finished=true;
    }
    ProcessHandler(bool *gay, HANDLE *HDcs):Job()
    {
        Dcs=HDcs;
        startproc=gay;
    }
    HANDLE *Dcs;
    bool *startproc;
    bool _done;
};

#endif // PROCESSHANDLER_H
