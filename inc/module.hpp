#ifndef MODULE_H
#define MODULE_H

class Module {
public:
    Module(int fd) { this->fd = fd; };
    ~Module() { close(fd); };
    
    int getFd() { return fd; };
    virtual int recv() = 0;
    
protected:
    int fd;
};

#endif // MODULE_H
