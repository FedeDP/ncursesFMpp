#ifndef NCURSESTAB_H
#define NCURSESTAB_H

#include <mytab.hpp>
#include <unordered_map>
#include <functional>

class FmTab : public MyTab
{
public:
    FmTab(bool hasSysLine, int starty = 0, int startx = 0, bool active = true);
    int process(int c) override;

private:
    void getFileList();
    int changeDir();
    
    std::vector<std::string> list;
    std::unordered_map<int, std::function<int(void)>> mapFunc;
    std::string cwd;
//     std::vector<Modality> &Mod;
//     Modality *currentMod;
};

#endif // NCURSESTAB_H
