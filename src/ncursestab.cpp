#include "ncursestab.hpp"

NcursesTab::NcursesTab(std::string t, int starty, int startx)
 : NCursesMenu(lines() - 3, cols() / 2, starty, startx)
{
    itemList.push_back(new NCursesMenuItem("top"));
    itemList.push_back(new NCursesMenuItem("kek"));
    itemList.push_back(new NCursesMenuItem("topkek"));
    itemList.push_back(new NCursesMenuItem("kektop"));
    itemList.push_back(new NCursesMenuItem());
    
    set_format(lines() - 5, 1); // 2 dimension of borders, 3 dimension of modtab win
    InitMenu(&itemList.front(), TRUE, TRUE);
    frame(t.c_str(), "FM");
    
    set_mark("-> ");
    curs_set(0);

    post();
    show();
    refresh();
}

int NcursesTab::virtualize(int c) {
//     if (activeMod.getCb(c) != nullptr) {
//         return activeMod.getCb(c);
//     }    
    return driver(NCursesMenu::virtualize(c));
}
