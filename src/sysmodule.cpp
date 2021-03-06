#include <sysmodule.hpp>
#include <sys/timerfd.h>
#include <ctype.h>
#include <sys/sysinfo.h>
#include <sstream>

// "time, sys, battery" by default
SysModule::SysModule() : sysinfoLayout(MyConfig::lookup("sysinfo_layout", std::string("tsb"))) {
    int timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timerfd == -1) {
        Log::getInstance().Warn("Could not start timer.");
    } else {
        struct itimerspec timerValue = {{0}};
        udev = udev_new();
        poll_batteries();
        timerValue.it_value.tv_sec = 0;
        timerValue.it_value.tv_nsec = 1;
        timerValue.it_interval.tv_sec = MyConfig::lookup("sysinfo_timeout", 30);
        timerValue.it_interval.tv_nsec = 0;
        timerfd_settime(timerfd, 0, &timerValue, NULL);
        Log::getInstance().Debug("Started time/battery monitor.");
    }
    setFd(timerfd);
}

SysModule::~SysModule() {
    udev_unref(udev);
}

int SysModule::recv() {
    uint64_t t;
    read(getFd(), &t, sizeof(uint64_t));
    
    sysTab.CUR_clrtoeol();
    for (int i = 0; i < sysinfoLayout.size(); i++) { 
        switch (tolower(sysinfoLayout[i])) {
        case 't':
            updateTimeDate(i);
            break;
        case 's':
            updateSysInfo(i);
            break;
        case 'b':
            updateBatt(i);
            break;
        default:
            break;
        }
    }
    sysTab.refresh();
    return 0;
}

void SysModule::updateTimeDate(int where) {
    std::stringstream date;
    
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    date << std::put_time(&tm, "%a %e %b %Y %k:%M");
    int x = checkSysinfoWhere(where, date.str().size());
    sysTab.printw(0, x, "%.*s", COLS, date.str().c_str());
}

void SysModule::updateSysInfo(int where) {
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;
    const double megabyte = 1024 * 1024;
    char sys_str[100];
    int len;
    struct sysinfo si;
    
    sysinfo(&si);
    sprintf(sys_str, "up: %ldd, %ldh, %02ldm, ", si.uptime / day, (si.uptime % day) / hour, 
            (si.uptime % hour) / minute);
    len = strlen(sys_str);
    sprintf(sys_str + len, "loads: %.2f, %.2f, %.2f, ", si.loads[0] / (float)(1 << SI_LOAD_SHIFT),
            si.loads[1] / (float)(1 << SI_LOAD_SHIFT),
            si.loads[2] / (float)(1 << SI_LOAD_SHIFT));
    float used_ram = (si.totalram - si.freeram) / megabyte;
    len = strlen(sys_str);
    sprintf(sys_str + len, "procs: %d, ram usage: %.1fMb/%.1fMb", si.procs, used_ram, si.totalram / megabyte);
    len = strlen(sys_str);
    int x = checkSysinfoWhere(where, len);
    sysTab.printw(0, x, "%.*s", COLS, sys_str);
}

void SysModule::updateBatt(int where) {
    struct udev_device *dev;
    std::vector<int> percs;
    int online;
    
    percs.reserve(battPaths.size());
    dev = udev_device_new_from_syspath(udev, acPath.c_str());
    if (dev && udev_device_get_property_value(dev, "POWER_SUPPLY_ONLINE")) {
        online = strtol(udev_device_get_property_value(dev, "POWER_SUPPLY_ONLINE"), NULL, 10);
        udev_device_unref(dev);
        if (!online) {
            for (auto& batt : battPaths) {
                dev = udev_device_new_from_syspath(udev, batt.c_str());
                if (dev && udev_device_get_property_value(dev, "POWER_SUPPLY_CAPACITY")) {
                    percs.emplace_back(strtol(udev_device_get_property_value(dev, "POWER_SUPPLY_CAPACITY"), NULL, 10));
                } else {
                    percs.emplace_back(-1);
                }
                udev_device_unref(dev);
            }
        }
    } else {
        online = -1;
    }
    printBatt(online, percs, where);
}

void SysModule::printBatt(int online, std::vector<int>& percs, int where) {
    std::vector<std::string> battStr;
    int x, i = 0, len = 0, lowLevel;
    
    switch (online) {
        case 1:
            /* ac connected */
            x = checkSysinfoWhere(where, strlen(_("On AC")));
            sysTab.printw(0, x, "%.*s", COLS, _("On AC"));
            break;
        case 0:
            /* on battery */
            // to workaround an issue if sysinfo layout set
            // battery mon on center, and we have more than one battery.
            // we must check total batteries strings length before, to print it centered.
            battStr.reserve(battNames.size());
            for (auto& n : battNames) {
                if (i > 1 && i < battNames.size() - 1) {
                    battStr.back().append(",");
                    len++;
                }
                std::stringstream s;
                s << n << ":" << percs.at(i) << "%";
                battStr.emplace_back(s.str());
                len += battStr.back().size();
                i++;
            }
            x = checkSysinfoWhere(where, len);
            i = 0;
            lowLevel = MyConfig::lookup("batt_low_level", 15);
            for (auto &s : battStr) {
                if (percs.at(i) <= lowLevel) {
                    sysTab.CUR_attron(COLOR_PAIR(5));
                }
                sysTab.printw(0, x, "%s", s.c_str());
                if (percs.at(i) <= lowLevel) {
                    sysTab.CUR_attroff(COLOR_PAIR(5));
                }
                i++;
            }
            break;
        default:
            x = checkSysinfoWhere(where, strlen(_("No power supply info available.")));
            sysTab.printw(0, x, "%.*s", COLS, _("No power supply info available."));
            break;
    }
}



int SysModule::checkSysinfoWhere(int where, int len) {
    return where ? where * (sysTab.cols() - len) / 2 : 1;
}

/*
* Initial battery polling: for each system battery,
* save its path in batt[].
* If property "POWER_SUPPLY_ONLINE" is present, then
* current udev device is ac adapter.
*/
void SysModule::poll_batteries(void) {
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "power_supply");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);
    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path = udev_list_entry_get_name(dev_list_entry);
        struct udev_device * dev = udev_device_new_from_syspath(udev, path);
        if (udev_device_get_property_value(dev, "POWER_SUPPLY_ONLINE")) {
            acPath = path;
        } else {
            battPaths.emplace_back(path);
            if (udev_device_get_property_value(dev, "POWER_SUPPLY_NAME")) {
                battNames.emplace_back(udev_device_get_property_value(dev, "POWER_SUPPLY_NAME"));
            } else {
                battNames.emplace_back("BAT");
            }
        }
        udev_device_unref(dev);
    }
    udev_enumerate_unref(enumerate);
}
