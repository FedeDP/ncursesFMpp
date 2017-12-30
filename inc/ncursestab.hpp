#ifndef NCURSESTAB_H
#define NCURSESTAB_H

#include <cursesm.h>
#include <string>
#include <vector>

class NcursesTab : public NCursesMenu
{
public:
    NcursesTab(const std::vector<std::string> &in, std::string t, int starty = 0, int startx = 0);
    ~NcursesTab();
    int virtualize(int c);
    
private:
//     std::vector<Modality> &Mod;
//     Modality *currentMod;
    std::vector<NCursesMenuItem *> itemList;
};

#endif // NCURSESTAB_H
