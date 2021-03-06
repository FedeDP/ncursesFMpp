#ifndef SYSMODULE_H
#define SYSMODULE_H

#include <module.hpp>
#include <systab.hpp>
#include <libudev.h>

class SysModule : public Module 
{
public:
    SysModule();
    ~SysModule();
    int recv() override;
    
private:
    void updateTimeDate(int where);
    void updateSysInfo(int where);
    void updateBatt(int where);
    int checkSysinfoWhere(int where, int len);
    void poll_batteries(void);
    void printBatt(int online, std::vector<int>& percs, int where);
    
    SysTab sysTab;
    std::string sysinfoLayout;
    struct udev *udev;
    std::string acPath;
    std::vector<std::string> battPaths;
    std::vector<std::string> battNames;
};

#endif // SYSMODULE_H
