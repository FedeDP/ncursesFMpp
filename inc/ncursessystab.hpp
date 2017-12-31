#ifndef NCURSESSYSTAB_H
#define NCURSESSYSTAB_H

#include <cursesm.h>
#include <vector>
#include <string>

class NcursesSysTab : public NCursesMenu
{
public:
    NcursesSysTab();
    int virtualize(int c);

private:
    std::vector<NCursesMenuItem *> modNames;
};

#endif // NCURSESSYSTAB_H
