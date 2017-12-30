/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  Federico Di Pierro <nierro92@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ncursesui.hpp"

NcursesUI::NcursesUI() : Module(STDIN_FILENO), NCursesApplication(FALSE) {
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
            if (activeWin == &modTab) {
                activeWin = &tabs.front();
            } else {
                activeWin = &modTab;
            }
            break;
        case 27: /* ESC to exit/leave special mode */
            ret = -1;
            break;
        case KEY_LEFT: // left to switch tab only if we're not choosing modality
            if (activeWin != &modTab) {
                if (activeWin != &tabs.back()) {
                    activeWin = &tabs.front();
                } 
                break;
            }
            // DO not break so it will be redirected to default case
        case KEY_RIGHT: // right to switch tab only if we're not choosing modality
            if (activeWin != &modTab) {
                if (activeWin != &tabs.front()) {
                    activeWin = &tabs.back();
                } 
                break;
            }
            // DO not break so it will be redirected to default case
        default:
            activeWin->virtualize(c);
            break;
    }
    activeWin->refresh();
    return ret;
}

int NcursesUI::run() {
    //     init_modalities(); // to be passed to tabs!
    list.push_back("top");
    list.push_back("kek");
    list.push_back("keeeeeeeeeeeeeeeeeeeeek");
    
    tabs.emplace_back(list, "Tab1");
    //     tabs.emplace_back(list, "Tab2", 0, COLS / 2);
    
    activeWin = &tabs.front();
    return 0; 
}
