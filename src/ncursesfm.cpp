#include <ncursesfm.hpp>
#include <ncursesui.hpp>
#include <sysmodule.hpp>
#include <experimental/filesystem>

NcursesFM::NcursesFM(int argc, char *argv[]) {
    if (argc == 1 || !setStartingDir(argv[1])) {
        std::string starting_dir = NcursesConfig::lookup("starting_directory", std::string());
        if (!starting_dir.empty()) {
            setStartingDir(starting_dir.c_str());
        }
    }
    
    modules.push_back(std::make_unique<NcursesUI>());
    pollfd fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
    
    modules.push_back(std::make_unique<SysModule>());
    fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
}

bool NcursesFM::setStartingDir(const char *cwd) const {
    bool ret = true;
    try {
        std::experimental::filesystem::current_path(cwd);
    } catch (std::experimental::filesystem::filesystem_error &err) {
        fprintf(stderr, "%s\n", err.what());
        ret = false;
    }
    return ret;
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
        
        for (int i = 0; i < fds.size() && r > 0 && !quit; i++) {
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
