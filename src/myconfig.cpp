#include "myconfig.hpp"
#include <log.hpp>

MyConfig::MyConfig() {
    try
    {
        cfg.readFile(CONFIG_PATH);
    }
    catch (const FileIOException &fioex)
    {
        Log::getInstance().Error("I/O error while reading file");
        exit(EXIT_FAILURE);
    }
    catch (const ParseException &pex)
    {
        Log::getInstance().Error("Parse error at", pex.getFile(), ":", pex.getLine(), "-", pex.getError());
        exit(EXIT_FAILURE);
    }
}
