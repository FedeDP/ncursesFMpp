#include <ncursesfm.hpp>
#include <ncursesui.hpp>
#include <sysmodule.hpp>

NcursesFM::NcursesFM() {
    modules.push_back(std::make_unique<NcursesUI>());
    pollfd fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
    
    modules.push_back(std::make_unique<SysModule>());
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
            Log::getInstance().Error(std::strerror(errno));
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
