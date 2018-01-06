#ifndef NCURSESFM_H
#define NCURSESFM_H

#include <poll.h>
#include <memory>
#include <module.hpp>
#include <cursesapp.h>

class NcursesFM : public NCursesApplication 
{
public:
    NcursesFM();
    int run();

private:
    bool setStartingDir(const char *cwd) const;
    void initLocale() const;
    void initCwd(void) const;
    void initModules();
    
    bool quit = false;
    std::vector<pollfd> fds;
    std::vector<std::unique_ptr<Module>> modules;
};

#endif // NCURSESFM_H
