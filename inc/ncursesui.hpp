#ifndef NCURSESUI_H
#define NCURSESUI_H

#include <ncursestab.hpp>
#include <ncursesmodtab.hpp>
#include <module.hpp>
#include <cursesapp.h>

class NcursesUI : public Module, public NCursesApplication 
{
public:
    NcursesUI();
    int recv();
    int run();
    
private:
    std::vector<std::unique_ptr<NcursesTab>> tabs;
    NcursesModTab modTab;
    MyNcursesMenu *activeWin, *lastActive; // last win active before changing modality

};

#endif // NCURSESUI_H
