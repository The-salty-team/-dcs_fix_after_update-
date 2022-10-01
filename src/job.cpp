#include "job.h"

Job::Job()
{
    finished=false;
    restartable=false;
}

Job:: ~Job()
{

}
void Job::run()
{
    finished=true;
}
