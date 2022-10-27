#include <iostream>
#include "jobMan.h"
#include "ProcessWatch.h"
#include "ProcessHandler.h"
#include "windows.h"
#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif
using namespace std;

int main()
{
    jobMan *jobman=new jobMan();
    HANDLE DcsU=nullptr;
    HANDLE Dcs=nullptr;
    bool gay=true;
    ProcessWatch *pw1=new ProcessWatch(&DcsU,"DCS_Updater.exe");
    ProcessWatch *pw2=new ProcessWatch(&Dcs,"DCS.exe");
    ProcessHandler *h1=new ProcessHandler(&gay,&DcsU);

auto filename = "D:/Games/DCS World/Config/graphics.lua";
auto filename2 =" D:/Games/DCS World/Scripts/DemoScenes/sceneVR.lua";
struct stat result;
if(stat(filename, &result)==0)
{
    time_t mod_time = result.st_mtime;
    cout<< asctime(gmtime(&mod_time));
}


    jobman->new_worker();
    jobMan::get_singleton()->add_job(h1);
    jobman->new_worker();
    jobMan::get_singleton()->add_job(pw1);
    jobman->new_worker();
    jobMan::get_singleton()->add_job(pw2);

    bool runonce=false;
    bool closedcs=true;
    bool finished=false;
    while(!finished)
    {
        finished=true;
        if(!pw1->finished)
        {
            finished=false;

        }
        if(pw1->finished && closedcs})
        {
            if(!runonce)
            {
                gay=false;
                jobMan::get_singleton()->add_job(h1);
                runonce=true;
            }
        }
        if(!pw2->finished)
        {
            finished=false;
        }
        if(h2->finished && !h1->finished)
        {
            finished=true;
            return;
        }
        if(!h1->finished)
        {
            finished=false;
        }
    }


    delete jobman;


    //TODO: Make job adding dynamic, start DCS exe first, inv python script etc.
    //use openprocess to check if process is running, do nothing if dcs.exe is running and updater isnt.
    //Make filenames dynamic
    //Also fix compiler cause the whole shit is broken as fuck.
    return 0;
}
