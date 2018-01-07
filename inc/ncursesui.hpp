#ifndef NCURSESUI_H
#define NCURSESUI_H

#include <fmtab.hpp>
#include <modtab.hpp>
#include <module.hpp>

class NcursesUI : public Module
{
public:
    NcursesUI(bool hasSysLine);
    int recv() override;
    
private:
    std::vector<std::unique_ptr<FmTab>> tabs;
    std::unique_ptr<ModTab> modTab;
    MyMenu *activeWin, *lastActive; // last win active before changing modality

};

#endif // NCURSESUI_H
