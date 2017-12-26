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

#ifndef LOG_H
#define LOG_H

#include <mutex>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <pwd.h>

class Log {
public:
    static Log& getInstance() {
        static Log instance;
        return instance;
    }
    
    template <typename... Args>
    void Debug(Args&&... args) {
        return logMessage(DEBUG, 'D', args...);
    }
    
    template <typename... Args>
    void Warn(Args&&... args) {
        return logMessage(WARN, 'W', args...);
    }
    
    template <typename... Args>
    void Error(Args&&... args) {
        return logMessage(ERROR, 'E', args...);
    }

private:
    Log() {
        // FIXME: load loglevel from conf
        this->logLevel = DEBUG;
        
        struct passwd *pw = getpwuid(getuid());
        std::string homedir = pw->pw_dir;
        
        logFile.open(homedir + "/.ncursesfm++.log");
    }
    
    ~Log() {
        logFile.close();
    }
    
    Log(Log const&) = delete;
    void operator=(Log const&) = delete;
    
    template <typename... Args>
    void logMessage(int level, char type, Args&&... args)
    {
        if (logFile.is_open() && level >= logLevel) {
            mtx.lock();
            logFile << "[" << type << "]";
            using expander = int[];
            (void)expander{0, (void(logFile << ' ' << std::forward<Args>(args)),0)...};
            std::flush(logFile);
            mtx.unlock();
        }
    }
    
    enum LogLevels { DEBUG, WARN, ERROR };
    
    std::ofstream logFile;
    int logLevel;
    std::mutex mtx;
};

#endif // LOG_H
