#ifndef SYSMODULE_H
#define SYSMODULE_H

#include <module.hpp>
#include <ncursessystab.hpp>

class SysModule : public Module 
{
public:
    SysModule();
    int recv();
    
private:
    NcursesSysTab sysTab;
};

#endif // SYSMODULE_H
