#ifndef NCURSESMODTAB_H
#define NCURSESMODTAB_H

#include <cursesm.h>
#include <log.hpp>

class NcursesModTab : public NCursesMenu
{
public:
    NcursesModTab();
    int virtualize(int c);

private:
    std::vector<NCursesMenuItem *> modNames;
};

#endif // NCURSESMODTAB_H
