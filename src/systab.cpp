#include "systab.hpp"

SysTab::SysTab()
: NCursesWindow(1, cols(), lines() - 1, 0)
{
    curs_set(0);
}
