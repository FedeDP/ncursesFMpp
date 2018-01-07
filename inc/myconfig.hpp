#ifndef NCURSESCONFIG_H
#define NCURSESCONFIG_H

#include <libconfig.h++>

using namespace libconfig;

class MyConfig
{
public:
    template <typename Arg>
    static Arg lookup(const char *option, Arg defaultValue) {
        static MyConfig conf;
        try {
            return conf.cfg.lookup(option);
        } catch(const SettingNotFoundException &nfex) {
            return defaultValue;
        }
    }
        
private:
    MyConfig();
    
    MyConfig(MyConfig const&) = delete;
    void operator=(MyConfig const&) = delete;

    Config cfg;
};

#endif // NCURSESCONFIG_H
