#ifndef NCURSESTAB_H
#define NCURSESTAB_H

#include <myncursesmenu.hpp>
#include <unordered_map>
#include <functional>

class NcursesTab : public MyNcursesMenu
{
public:
    NcursesTab(bool hasSysLine, int starty = 0, int startx = 0, bool active = true);
    int process(int c);

private:
    void getFileList();
    int changeDir();
    
    std::vector<std::string> list;
    std::unordered_map<int, std::function<int(void)>> mapFunc;
//     std::vector<Modality> &Mod;
//     Modality *currentMod;
};

#endif // NCURSESTAB_H
