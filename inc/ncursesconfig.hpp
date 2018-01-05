#ifndef NCURSESCONFIG_H
#define NCURSESCONFIG_H

#include <libconfig.h++>

using namespace libconfig;

class NcursesConfig
{
public:
    template <typename Arg>
    static Arg lookup(const char *option, Arg defaultValue) {
        static NcursesConfig conf;
        try {
            return conf.cfg.lookup(option);
        } catch(const SettingNotFoundException &nfex) {
            return defaultValue;
        }
    }
        
private:
    NcursesConfig();
    
    NcursesConfig(NcursesConfig const&) = delete;
    void operator=(NcursesConfig const&) = delete;

    Config cfg;
};

#endif // NCURSESCONFIG_H
