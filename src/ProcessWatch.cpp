#include "ProcessWatch.h"

ProcessWatch::ProcessWatch()
{
    //ctor
}

ProcessWatch::HANDLE GetProcessName(LPCTSTR Name, DWORD dwAccess)
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
ProcessWatch::~ProcessWatch()
{
    //dtor
}
