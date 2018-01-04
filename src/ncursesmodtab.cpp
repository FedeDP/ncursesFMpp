#include <ncursesmodtab.hpp>

NcursesModTab::NcursesModTab()
 : MyNcursesMenu(_("Modalities"), _("Press TAB to switch"), "*", 3, cols(), lines() - 4, 0)
{
    itemList.reserve(9);
    itemList.push_back(new NCursesMenuItem(_("1. Browse")));
    itemList.push_back(new NCursesMenuItem(_("2. FM")));
    itemList.push_back(new NCursesMenuItem(_("3. Places")));
    itemList.push_back(new NCursesMenuItem(_("4. Stats")));
    itemList.push_back(new NCursesMenuItem(_("5. Selected")));
    itemList.push_back(new NCursesMenuItem(("6. Search")));
    itemList.push_back(new NCursesMenuItem(_("7. Helper")));
    itemList.push_back(new NCursesMenuItem(_("8. Notifications")));
    itemList.push_back(new NCursesMenuItem());

    set_format(1, cols() - 2);
    MyNcursesMenu::init();
}
