#include <sysmodule.hpp>
#include <sys/timerfd.h>

SysModule::SysModule() {
    int timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timerfd == -1) {
        Log::getInstance().Warn("Could not start timer.");
    } else {
        struct itimerspec timerValue = {{0}};
//         udev = udev_new();
//         poll_batteries();
        timerValue.it_value.tv_sec = 0;
        timerValue.it_value.tv_nsec = 1;
        timerValue.it_interval.tv_sec = 30;
        timerValue.it_interval.tv_nsec = 0;
        timerfd_settime(timerfd, 0, &timerValue, NULL);
        Log::getInstance().Debug("Started time/battery monitor.");
    }
    setFd(timerfd);
}

int SysModule::recv() {
    uint64_t t;
    read(getFd(), &t, sizeof(uint64_t));
    
    Log::getInstance().Debug("To be implemented!");
    return 0;
}

