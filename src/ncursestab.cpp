#include <ncursestab.hpp>

NcursesTab::NcursesTab(std::string t, int starty, int startx)
 : NCursesMenu(lines() - 4, cols() / 2, starty, startx)
{
    itemList.push_back(new NCursesMenuItem("top"));
    itemList.push_back(new NCursesMenuItem("kek"));
    itemList.push_back(new NCursesMenuItem("topkek"));
    itemList.push_back(new NCursesMenuItem("kektop"));
    itemList.push_back(new NCursesMenuItem());
    
    set_format(lines() - 2 - 4, 1); // 2 dimension of borders, 4 dimension of modtab win + syswin
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
