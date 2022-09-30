#include "job.h"

job::job()
{
    finished=false;
}

job::~job()
{
    finished=true;
}
