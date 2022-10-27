#ifndef PROCESSWATCH_H
#define PROCESSWATCH_H
#include "job.h"
#include <sstream>

class ProcessWatch : public Job
{
    public:
        LPCTSTR Name;
        HANDLE *hDcs;
        HANDLE GetProcessName(LPCTSTR Name, DWORD dwAccess)
        {
            HANDLE hsnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
            if(hsnap!=INVALID_HANDLE_VALUE)
            {
                PROCESSENTRY32 pe;
                ZeroMemory(&pe,sizeof(PROCESSENTRY32));
                pe.dwSize=sizeof(PROCESSENTRY32);
                Process32First(hsnap,&pe);
                do
                {
                    if(!lstrcmpi(pe.szExeFile,Name)) return OpenProcess(dwAccess,0,pe.th32ProcessID);
                }
                while(Process32Next(hsnap,&pe));
            }
            return INVALID_HANDLE_VALUE;
        }
        std::stringstream stream;
        string out;
        void run()
        {
            if(Name=="DCS.exe") this_thread::sleep_for(chrono::milliseconds(5000));
                bool runonce=false;
                stream<<"Getting Handle for "<<Name<<endl;
                out=stream.str();
                cout<<out;
                out="";
                stream.str("");
                do
                {
                 if(runonce)
                  {
                    stream<<"Handle not found for "<<Name<<", retrying...."<<endl;
                    *hDcs=nullptr;
                    out=stream.str();
                    cout<<out;
                    finished=false;
                    stream.str("");
                    this_thread::sleep_for(chrono::milliseconds(5000));
                  }
                  if(!runonce) runonce=true;

                  *hDcs=GetProcessName(Name,PROCESS_ALL_ACCESS);
                }
                while(*hDcs==nullptr || *hDcs==INVALID_HANDLE_VALUE);
                stream<<"Got handle for "<<Name<<": "<<*hDcs<<endl;
                out=stream.str();
                cout<<out;
                finished=true;

        }
        ProcessWatch(HANDLE *HDCS, LPCTSTR name) : Job()
        {
            Name=name;
            hDcs=HDCS;
        }


};

#endif // PROCESSWATCH_H
