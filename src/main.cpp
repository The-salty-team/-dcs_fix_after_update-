#include <iostream>
#include "jobMan.h"
#include "ProcessWatch.h"
#include "windows.h"
using namespace std;

int main()
{
    jobMan *jobman=new jobMan();
    HANDLE *DcsU=nullptr;
    HANDLE *Dcs=nullptr;
    ProcessWatch pw=new ProcessWatch(&Dcsu,"DCS_Updater.exe");
    ProcessWatch pw=new ProcessWatch(&Dcs,"DCS.exe");
    jobMan::new_worker();
    jobMan::get_singleton()->add_job(&pw)
    return 0;
}
