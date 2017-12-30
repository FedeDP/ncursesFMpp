#include "ncursesmodtab.hpp"

NcursesModTab::NcursesModTab()
: NCursesMenu(3, cols(), lines() - 3, 0)
{    
    modNames.reserve(6);
    modNames.push_back(new NCursesMenuItem("1. Browse"));
    modNames.push_back(new NCursesMenuItem("2. FM"));
    modNames.push_back(new NCursesMenuItem("3. Places"));
    modNames.push_back(new NCursesMenuItem("4. Stats"));
    modNames.push_back(new NCursesMenuItem("5. Notifications"));
    modNames.push_back(new NCursesMenuItem());
    
    set_format(1, cols() - 2);
    InitMenu(&modNames.front(), TRUE, TRUE);
    frame("Modalities", "Choose");
    
    set_mark("*");
    curs_set(0);
    
    post();
    show();
    refresh();
}

int NcursesModTab::virtualize(int c) {
    return driver(NCursesMenu::virtualize(c));
}
