#include "ncursesui.hpp"

NcursesUI::NcursesUI() : Module(STDIN_FILENO), NCursesApplication(false) {
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_RED, -1);
    ESCDELAY = 25;
//     raw();
    
    // start our NCursesApplication (create stdscr win etc etc)
    NCursesApplication::operator()();
}

NcursesUI::~NcursesUI() { }

int NcursesUI::recv() {
    int ret = 0;
    
    int c = activeWin->getch();
    switch (c) {
        case 9: // tab to switch!
            activeWin->setEnabled(false);
            if (activeWin == &modTab) {
                activeWin = lastActive;
                activeWin->setEnabled(true);
            } else {
                lastActive = activeWin;
                activeWin = &modTab;
                activeWin->setEnabled(true);
            }
            break;
        case 27: /* ESC to exit */
            ret = -1;
            break;
        case KEY_LEFT: // left to switch tab only if we're not choosing modality
            if (activeWin != &modTab) {
                if (activeWin != tabs.front().get()) {
                    activeWin->setEnabled(false);
                    activeWin = tabs.front().get();
                    activeWin->setEnabled(true);
                } 
                break;
            }
            // DO not break so it will be redirected to default case
        case KEY_RIGHT: // right to switch tab only if we're not choosing modality
            if (activeWin != &modTab) {
                if (activeWin != tabs.back().get() && tabs.size() == 2) {
                    activeWin->setEnabled(false);
                    activeWin = tabs.back().get();
                    activeWin->setEnabled(true);
                } 
                break;
            }
            // DO not break so it will be redirected to default case
        default:
            activeWin->process(c);
            break;
    }
    activeWin->refresh();
    return ret;
}

int NcursesUI::run() {
    //     init_modalities(); // to be passed to tabs!
    
    tabs.emplace_back(new NcursesTab("Tab1"));
    tabs.emplace_back(new NcursesTab("Tab2", 0, COLS / 2));
    
    activeWin = tabs.front().get();
    activeWin->setEnabled(true);
    return 0; 
}
