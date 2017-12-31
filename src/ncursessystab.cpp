#include "ncursessystab.hpp"

NcursesSysTab::NcursesSysTab()
: NCursesMenu(1, cols(), lines() - 1, 0)
{
    modNames.reserve(4);
    modNames.push_back(new NCursesMenuItem("Timedate"));
    modNames.push_back(new NCursesMenuItem("CPU"));
    modNames.push_back(new NCursesMenuItem("Batt"));
    modNames.push_back(new NCursesMenuItem());
    
    set_format(1, cols());
    InitMenu(&modNames.front(), FALSE, TRUE);
    
    curs_set(0);
    
    post();
    show();
    refresh();
}

int NcursesSysTab::virtualize(int c) {
    return 0; // disabled
}
