#ifndef SYSMODULE_H
#define SYSMODULE_H

#include <module.hpp>

class SysModule : public Module 
{
public:
    SysModule();
    int recv();
};

#endif // SYSMODULE_H
