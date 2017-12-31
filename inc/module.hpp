#ifndef MODULE_H
#define MODULE_H

#include <log.hpp>

class Module 
{
public:
    Module() {};
    Module(int fd) { this->fd = fd; };
    ~Module() { close(fd); };
    int getFd() { return fd; };
    virtual int recv() = 0;
    
protected:
    void setFd(int fd) { this->fd = fd; }

private:
    int fd;
};

#endif // MODULE_H
