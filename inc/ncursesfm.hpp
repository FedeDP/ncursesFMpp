#ifndef NCURSESFM_H
#define NCURSESFM_H

#include <poll.h>
#include <memory>
#include <module.hpp>

class NcursesFM
{
public:
    NcursesFM(int argc, char *argv[]);
    int operator()(void);

private:
    void loop();
    
    bool quit = false;
    std::vector<pollfd> fds;
    std::vector<std::unique_ptr<Module>> modules;
};

#endif // NCURSESFM_H
