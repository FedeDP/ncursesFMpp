#include "mytab.hpp"

MyTab::MyTab(std::string title, std::string label, std::string mark,
                             int nlines, int ncols, int starty, int startx, bool active) 
 : NCursesMenu(nlines, ncols, starty, startx) {
    this->title = title;
    this->label = label;
    this->mark = mark;
    this->active = active;
}

void MyTab::init() {
    InitMenu(itemList.data(), TRUE, TRUE);
    
    setActive(active);
    set_mark(mark.c_str());
    curs_set(0);
    options_off(O_SHOWDESC);
    post();
    show();
    refresh();
}

int MyTab::process(int c) {
    return driver(NCursesMenu::virtualize(c));
}

void MyTab::setActive(bool active) {
    this->active = active;
    if (active) {
        CUR_attron(COLOR_PAIR(3));
    }
    frame(title.c_str(), label.c_str());
    if (active) {
        CUR_attroff(COLOR_PAIR(3));
    }
}

void MyTab::updateItems(std::string title) {
    if (!title.empty()) {
        this->title = title;
    }
    unpost();
    setItems(itemList.data());
    if (!title.empty()) {
        setActive(active);
    }
    post();
    refresh();
}

