#ifndef NCURSESTAB_H
#define NCURSESTAB_H

#include <myncursesmenu.hpp>

class NcursesTab : public MyNcursesMenu
{
public:
    NcursesTab(std::string t, int starty = 0, int startx = 0);
    int process(int c);
    
private:
//     std::vector<Modality> &Mod;
//     Modality *currentMod;
};

#endif // NCURSESTAB_H
