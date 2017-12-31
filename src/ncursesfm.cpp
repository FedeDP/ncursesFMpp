#include <ncursesfm.hpp>
#include <string.h>
#include <log.hpp>
#include <ncursesui.hpp>
#include <sysmodule.hpp>

NcursesFM::NcursesFM() {
    modules.emplace_back(new NcursesUI);
    pollfd fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
    
    modules.emplace_back(new SysModule);
    fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
}

NcursesFM::~NcursesFM() {
    
}

void NcursesFM::loop() {
    while (!quit) {
        int r = poll(&fds[0], fds.size(), -1);
        if (r == -1) {
            if (errno == EINTR) {
                continue;
            }
            Log::getInstance().Error(strerror(errno));
            quit = true;
        }
        
        for (int i = 0; i < fds.size() && r > 0; i++) {
            if (fds.at(i).revents & POLLIN) {
                if (modules.at(i)->recv() == -1) {
                    quit = true;
                }
                r--;
            }
        }
    }
}
