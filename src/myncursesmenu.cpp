#include "myncursesmenu.hpp"

MyNcursesMenu::MyNcursesMenu(std::string title, std::string label, std::string mark,
                             int nlines, int ncols, int starty, int startx) 
 : NCursesMenu(nlines, ncols, starty, startx) {
    this->title = title;
    this->label = label;
    this->mark = mark;
}

void MyNcursesMenu::init() {
    InitMenu(&itemList.front(), TRUE, TRUE);
    frame(title.c_str(), label.c_str());
    
    set_mark(mark.c_str());
    curs_set(0);
    
    post();
    show();
    refresh();
}

int MyNcursesMenu::process(int c) {
    return driver(NCursesMenu::virtualize(c)); 
}


void MyNcursesMenu::setEnabled(bool enabled) {
    if (enabled) {
        CUR_attron(COLOR_PAIR(3));
    }

    frame(title.c_str(), label.c_str());
    
    if (enabled) {
        CUR_attroff(COLOR_PAIR(3));
    }
}

