#include <ncursesmodtab.hpp>

NcursesModTab::NcursesModTab()
 : MyNcursesMenu("Modalities", "Choose", "*", 3, cols(), lines() - 4, 0)
{
    itemList.reserve(9);
    itemList.push_back(new NCursesMenuItem("1. Browse"));
    itemList.push_back(new NCursesMenuItem("2. FM"));
    itemList.push_back(new NCursesMenuItem("3. Places"));
    itemList.push_back(new NCursesMenuItem("4. Stats"));
    itemList.push_back(new NCursesMenuItem("5. Selected"));
    itemList.push_back(new NCursesMenuItem("6. Search"));
    itemList.push_back(new NCursesMenuItem("7. Helper"));
    itemList.push_back(new NCursesMenuItem("8. Notifications"));
    itemList.push_back(new NCursesMenuItem());

    set_format(1, cols() - 2);
    MyNcursesMenu::init();
}
