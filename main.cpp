#include "ncursesfm.hpp"
#include "log.hpp"
#include <libintl.h>
#include <langinfo.h>

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "");
    if (strcmp(nl_langinfo(CODESET), "UTF-8")) {
        fprintf(stderr, "Please use an utf8 locale.\n");
    }
    bindtextdomain("ncursesFM++", LOCALEDIR);
    textdomain("ncursesFM++");
    
    printf("%s\n", LOCALEDIR);
    
    NcursesFM fm(argc, argv);
    return fm();
}
