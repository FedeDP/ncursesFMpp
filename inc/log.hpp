#ifndef LOG_H
#define LOG_H

#include <mutex>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <iomanip>
#include <ctime>

class Log 
{
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
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            logFile << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << "::" << type << "::";
            using expander = int[];
            (void)expander{0, (void(logFile << ' ' << std::forward<Args>(args)),0)...};
            logFile << std::endl;
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
