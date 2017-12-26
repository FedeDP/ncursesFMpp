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

NcursesUI::NcursesUI() : Module(STDIN_FILENO) {
    initscr();
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_RED, -1);
    noecho();
    curs_set(0);
    mouseinterval(0);
    ESCDELAY = 25;
    raw();
    nodelay(stdscr, TRUE);
    
    //     init_modalities();
    //     for (auto t : tabs) {
    //         t.init(modalities); // FIXME: store a reference to modalities and set a reference to current modality
    //     }
    //     fullNameWin.init();
    //     sysWin.init();
}

NcursesUI::~NcursesUI() {
    if (stdscr) {
//         for (auto t : tabs) {
//             t.destroy(); // FIXME: needed to call inotify unload on tabs
//         }
        delwin(stdscr);
        endwin();
    }
}

int NcursesUI::recv() {
    wint_t c;
    wget_wch(stdscr, &c);
//     currentMod.mainSwitch(c);
    printf("Event %c!\n", c);
    return c;
}
