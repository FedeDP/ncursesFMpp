#include "ncursestab.hpp"

NcursesTab::NcursesTab(const std::vector<std::string> &in, std::string t, int starty, int startx)
 : NCursesMenu(lines() - 3, cols() / 2, starty, startx)
{
    itemList.reserve(in.size() + 1U);
    for (auto& s : in) {
        itemList.push_back(new NCursesMenuItem(s.c_str()));
    }
    itemList.push_back(new NCursesMenuItem());
    
    set_format(lines() - 2, 1); // 2 dimension of borders
    InitMenu(&itemList.front(), TRUE, TRUE);
    frame(t.c_str(), "FM");
    
    set_mark("-> ");
    curs_set(0);
        
    post();
    show();
    refresh();
}

NcursesTab::~NcursesTab() { }

int NcursesTab::virtualize(int c) {
//     if (activeMod.getCb(c) != nullptr) {
//         return activeMod.getCb(c);
//     }    
    return driver(NCursesMenu::virtualize(c));
}
