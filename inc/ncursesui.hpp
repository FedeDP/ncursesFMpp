#ifndef NCURSESUI_H
#define NCURSESUI_H

#include <ncursestab.hpp>
#include <ncursesmodtab.hpp>
#include "log.hpp"
#include <module.hpp>
#include <cursesapp.h>

class NcursesUI : public Module, public NCursesApplication {
public:
    NcursesUI();
    ~NcursesUI();
    int recv();
    int run();
    
private:
    std::vector<NcursesTab> tabs;
    NcursesModTab modTab;
    std::vector<std::string> list;
    NCursesMenu *activeWin;
//     Window sysWin;

};

#endif // NCURSESUI_H
