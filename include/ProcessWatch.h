#ifndef PROCESSWATCH_H
#define PROCESSWATCH_H
#include "job.h"

class ProcessWatch : public job
{
    public:
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


        void run()
        {


                Name="DCS_Updater.exe";
                cout<<"Getting Handle for"<<Name<< endl;
                do
                {
                  hDcs=GetProcessName(Name,PROCESS_VM_READ)
                }
                while(hDcs==nullptr || hDcs == INVALID_HANDLE_VALUE)
                cout<<"Got handle for updater";
                finished=true;
        }
        ProcesWatch(ProcessWatch pw=new ProcessWatch(Dcsu,"DCS_Updater.exe");) : job()
        {

        }
};

#endif // PROCESSWATCH_H
