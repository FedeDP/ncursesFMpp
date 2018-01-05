#include "ncursesconfig.hpp"
#include <log.hpp>

NcursesConfig::NcursesConfig() {
    try
    {
        // FIXME!
        cfg.readFile("/home/federico/Progetti/ncursesFM++/Extra/ncursesFM.conf");
    }
    catch (const FileIOException &fioex)
    {
        Log::getInstance().Error("I/O error while reading file.");
        exit(EXIT_FAILURE);
    }
    catch (const ParseException &pex)
    {
        Log::getInstance().Error("Parse error at", pex.getFile(), ":", pex.getLine(), "-", pex.getError());
        exit(EXIT_FAILURE);
    }
}
