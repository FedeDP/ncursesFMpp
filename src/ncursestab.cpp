#include <ncursestab.hpp>
#include <experimental/filesystem>

using namespace std::experimental::filesystem;

NcursesTab::NcursesTab(int starty, int startx, bool active)
: MyNcursesMenu(current_path().string(), _("Browse"), NcursesConfig::lookup("fm_cursor_chars", std::string("-> ")), lines() - 4, cols() / 2, starty, startx, active)
{    
    set_format(lines() - 2 - 4, 1); // 2 dimension of borders, 4 dimension of modtab win + syswin
//     NcursesConfig::lookup("fm_cursor_chars", mark, std::string("-> "));
    getFileList();
    MyNcursesMenu::init();
    
    mapFunc.emplace(10,  std::bind(&NcursesTab::changeDir, this));
}

int NcursesTab::process(int c) {
    try {
        return mapFunc.at(c)();
    } catch (const std::out_of_range& oor) {
        return MyNcursesMenu::process(c);
    }
}

void NcursesTab::getFileList() {
    list.clear();
    itemList.clear();
    
    for (auto& p : directory_iterator(current_path())) {
        std::string str;
        try {
            str = p.path().filename().string().substr(0, cols() / 2 - 3);
        } catch (const std::out_of_range& oor) {
            str = p.path().filename().string();
        }
        list.push_back(str);
    }
    
    // FIXME: why is this needed? Can't we directly use loop above?
    // ncurses prints weird things...
    for (auto& s : list) {
        itemList.push_back(new NCursesMenuItem(s.c_str()));
    }
    itemList.push_back(new NCursesMenuItem());
}

int NcursesTab::changeDir() {
    if (is_directory(current_item()->name())) {
        current_path(current_item()->name());
        getFileList();
        updateItems(current_path().string());
    }
    return 0;
}
