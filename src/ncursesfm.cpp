#include <ncursesfm.hpp>
#include <ncursesui.hpp>
#include <sysmodule.hpp>
#include <experimental/filesystem>

NcursesFM::NcursesFM(int argc, char *argv[]) {
    if (argc > 1) {
        try {
            std::experimental::filesystem::current_path(argv[1]);
        } catch (std::experimental::filesystem::filesystem_error &err) {
            fprintf(stderr, "%s\n", err.what());
        }
    }
    
    modules.push_back(std::make_unique<NcursesUI>());
    pollfd fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
    
    modules.push_back(std::make_unique<SysModule>());
    fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
}

int NcursesFM::operator()(void) {
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
    return 0;
}
