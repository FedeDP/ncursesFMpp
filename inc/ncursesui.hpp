#ifndef NCURSESUI_H
#define NCURSESUI_H

#include <ncursestab.hpp>
#include <ncursesmodtab.hpp>
#include <module.hpp>

class NcursesUI : public Module
{
public:
    NcursesUI(bool hasSysLine);
    int recv();
    
private:
    std::vector<std::unique_ptr<NcursesTab>> tabs;
    std::unique_ptr<NcursesModTab> modTab;
    MyNcursesMenu *activeWin, *lastActive; // last win active before changing modality

};

#endif // NCURSESUI_H
