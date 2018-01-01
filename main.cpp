#include "ncursesfm.hpp"
#include "log.hpp"
// #include "Module.hpp"

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "");
    
    NcursesFM fm;
    fm.loop();
    return 0;
}
