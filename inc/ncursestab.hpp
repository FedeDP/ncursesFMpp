#ifndef NCURSESTAB_H
#define NCURSESTAB_H

#include <cursesm.h>
#include <log.hpp>

class NcursesTab : public NCursesMenu
{
public:
    NcursesTab(std::string t, int starty = 0, int startx = 0);
    int virtualize(int c);
    
private:
//     std::vector<Modality> &Mod;
//     Modality *currentMod;
    std::vector<NCursesMenuItem *> itemList;
};

#endif // NCURSESTAB_H
