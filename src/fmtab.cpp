#include <fmtab.hpp>
#include <experimental/filesystem>

using namespace std::experimental::filesystem;

FmTab::FmTab(bool hasSysLine, int starty, int startx, bool active)
: MyTab(current_path().string(), _("Browse"), MyConfig::lookup("fm_cursor_chars", std::string("-> ")), lines() - 3 - hasSysLine, cols() / 2, starty, startx, active)
{    
//     cwd = current_path();
    set_format(lines() - 2 - 4, 1); // 2 dimension of borders, 4 dimension of modtab win + syswin
    getFileList();
    MyTab::init();
    mapFunc.emplace(10,  std::bind(&FmTab::changeDir, this));
}

int FmTab::process(int c) {
    try {
        return mapFunc.at(c)();
    } catch (const std::out_of_range& oor) {
        return MyTab::process(c);
    }
}

void FmTab::getFileList() {
    list.clear();
    itemList.clear();
    
    for (auto& p : directory_iterator(current_path())) {
        std::string str;
        try {
            str = p.path().filename().string().substr(0, cols() / 2 - 3);
        } catch (const std::out_of_range& oor) {
            str = p.path().filename().string();
        }
        list.emplace_back(str);
    }
    
    // FIXME: why is this needed? Can't we directly use loop above?
    // ncurses prints weird things...
    itemList.reserve(list.size() + 1);
    for (auto& s : list) {
        itemList.emplace_back(new NCursesMenuItem(s.c_str()));
    }
    itemList.emplace_back(new NCursesMenuItem());
}

int FmTab::changeDir() {
    if (is_directory(current_item()->name())) {
        current_path(current_item()->name());
        getFileList();
        updateItems(current_path().string());
    }
    return 0;
}
