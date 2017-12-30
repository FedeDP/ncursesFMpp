#ifndef NCURSESFM_H
#define NCURSESFM_H

#include <poll.h>
#include <memory>
#include "ncursesui.hpp"

class NcursesFM
{
public:
    NcursesFM();
    ~NcursesFM();
    void loop();

private:
    bool quit = false;
    std::vector<pollfd> fds;
    std::vector<std::unique_ptr<Module>> modules;
};

#endif // NCURSESFM_H
