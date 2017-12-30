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

#include "ncursesfm.hpp"
#include <string.h>

NcursesFM::NcursesFM() {
    modules.emplace_back(new NcursesUI);
    
    pollfd fgetch = { modules.back()->getFd(), POLLIN };
    fds.push_back(fgetch);
}

NcursesFM::~NcursesFM() {
    
}

void NcursesFM::loop() {
    while (!quit) {
        int r = poll(&fds[0], fds.size(), -1);
        if (r == -1) {
            if (errno == EINTR) {
                continue;
            }
            Log::getInstance().Error(strerror(errno));
            quit = true;
        }
        
        for (int i = 0; i < fds.size() && r > 0; i++) {
            if (fds.at(i).revents & POLLIN) {
                if (modules.at(i)->recv() == -1) {
                    quit = true;
                }
                r--;
            }
        }
    }
}
