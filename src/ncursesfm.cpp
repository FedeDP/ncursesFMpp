#include <ncursesfm.hpp>
#include <ncursesui.hpp>
#include <sysmodule.hpp>
#include <experimental/filesystem>
#include <libintl.h>
#include <langinfo.h>
#include <algorithm>

/* This will execute program even without a main */
static NcursesFM fm;

NcursesFM::NcursesFM() : NCursesApplication(false) {
    initLocale();
}

void NcursesFM::initLocale() const {
    std::setlocale(LC_ALL, "");
    if (strcmp(nl_langinfo(CODESET), "UTF-8")) {
        Log::getInstance().Error("Please use an utf8 locale.");
    }
    bindtextdomain("ncursesFM++", LOCALEDIR);
    textdomain("ncursesFM++");
}

void NcursesFM::initModules() {
    std::string sysLayout = MyConfig::lookup("sysinfo_layout", std::string("tsb"));
    
    /* Check that string is not empty and contains non-space chars */
    bool sysLayoutEmpy = std::all_of(sysLayout.begin(), sysLayout.end(), isspace);
    
    modules.push_back(std::make_unique<NcursesUI>(!sysLayoutEmpy));
    pollfd fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
    
    if (!sysLayoutEmpy) {
        modules.push_back(std::make_unique<SysModule>());
        fgetch = { modules.back()->getFd(), POLLIN };
        fds.push_back(fgetch);
    }
}

bool NcursesFM::setStartingDir(const char *cwd) const {
    bool ret = true;
    try {
        std::experimental::filesystem::current_path(cwd);
    } catch (std::experimental::filesystem::filesystem_error &err) {
        Log::getInstance().Error(err.what());
        ret = false;
    }
    return ret;
}

void NcursesFM::handleArgs(int argc, char *argv[]) {
    if (argc == 1 || !setStartingDir(argv[1])) {
        std::string starting_dir = MyConfig::lookup("starting_directory", std::string());
        if (!starting_dir.empty()) {
            setStartingDir(starting_dir.c_str());
        }
    }
}


int NcursesFM::run(void) {
    /* 
     * Needs to be called here as only after run()
     * NCursesApplication has fully inited ncurses screen.
     */
    initModules();
    
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
