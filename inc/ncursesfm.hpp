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

#ifndef NCURSESFM_H
#define NCURSESFM_H

#include <poll.h>
#include <memory>
#include "ncursesui.hpp"

class NcursesFM
{
public:
    NcursesFM();
    ~NcursesFM();
    void loop();

private:
    bool quit = false;
    std::vector<pollfd> fds;
    std::vector<std::unique_ptr<Module>> modules;
};

#endif // NCURSESFM_H
