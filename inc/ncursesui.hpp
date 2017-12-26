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

#ifndef NCURSESUI_H
#define NCURSESUI_H

#include <ncurses.h>
#include <vector>
#include "log.hpp"
#include "module.hpp"
// #include <Window.hpp>

class NcursesUI : public Module {
public:
    NcursesUI();
    ~NcursesUI();
    int recv();
    
private:
//     std::vector<FmTab> tabs;
//     Window sysWin;
//     Window fullNameWin;

};

#endif // NCURSESUI_H
