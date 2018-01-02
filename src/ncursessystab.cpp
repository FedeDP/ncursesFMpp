#include "ncursessystab.hpp"

NcursesSysTab::NcursesSysTab()
: NCursesWindow(1, cols(), lines() - 1, 0)
{
    curs_set(0);
}
