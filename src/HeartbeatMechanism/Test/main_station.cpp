#include "heartbeatsMechanism.h"
#include <iostream>
#include <thread>
#include <unistd.h>
//This function will be called from a thread

int main()
{
    HeartbeatsMechanism smy("10.42.0.251", 5557, 5556, false);
    sleep(1000);

    return 0;
}