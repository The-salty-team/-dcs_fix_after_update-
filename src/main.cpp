#include <iostream>

#include "windows.h"




#include <sys/types.h>
#include <sys/stat.h>
#include <Python.h>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

#include "jobMan.h"
#include "ProcessWatch.h"
#include "ProcessHandler.h"

using namespace std;

void GetModDate(time_t *moddate, auto Fname)
{
        struct stat result;
    if(stat(Fname, &result)==0)
    {
        *moddate= result.st_mtime;
        cout<< asctime(gmtime(moddate));
    }
}

int main()
{
    jobMan *jobman=new jobMan();
    HANDLE DcsU=nullptr;
    HANDLE Dcs=nullptr;
    bool gay=true;
    ProcessWatch *pw1=new ProcessWatch(&DcsU,"DCS_Updater.exe");
    ProcessWatch *pw2=new ProcessWatch(&Dcs,"DCS.exe");
    ProcessHandler *h1=new ProcessHandler(&gay,&DcsU);
    ProcessHandler *h2=new ProcessHandler(&gay,&Dcs);
    auto filename = "../Config/graphics.lua";
    auto filename2 ="../Scripts/DemoScenes/sceneVR.lua";

    time_t mod_time=NULL;
    time_t OriginalDate=NULL;

    GetModDate(&OriginalDate,filename);

    for(int i=0;i<3;++i)
    {
        jobman->new_worker();
    }
    jobMan::get_singleton()->add_job(h1);
    jobMan::get_singleton()->add_job(pw1);
    jobMan::get_singleton()->add_job(pw2);

    bool runonce=false;
    bool closedcs=false;
    bool finished=false;
    while(!finished)
    {
        if(DcsU!=nullptr || DcsU!=INVALID_HANDLE_VALUE && Dcs!=nullptr || Dcs!=INVALID_HANDLE_VALUE) closedcs=true;

        finished=true;
        if(!pw1->finished)
        {
            finished=false;

        }
        if(pw1->finished && closedcs)
        {
            if(!runonce)
            {
                gay=false;
                jobMan::get_singleton()->add_job(h2);
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
        }
        if(h2->finished && closedcs==true)
        {
            finished=false;
            GetModDate(&mod_time,filename);
            if(mod_time!=OriginalDate)
            {
                Py_Initialize();
                PyObject* sysPath = PySys_GetObject("path");
                PyList_Append(sysPath, PyUnicode_FromString("../Script/editor.py"));

                PyObject *pName = PyUnicode_FromString("editor");
                PyObject *pModule = PyImport_Import(pName);
                PyObject *pDict;
                if (pModule != NULL)
                {
                    std::cout << "Python module found\n";
                    std::cout << "Modifying graphics.lua and SceneVR.lua\n";
                    pDict = PyModule_GetDict(pModule);
                    if(pFunc != NULL){
                        PyObject_CallObject(pFunc, NULL);
                    } else {
                        std::cout << "Couldn't find func\n";
                    }
                 }

            }
            else
            {
                gay=true;
                jobMan::get_singleton()->add_job(h1);
            }
            finished=true;
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

    //pipe/socket for in between transportation of info
    return 0;
}
