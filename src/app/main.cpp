#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include "wsjcpp_package_manager.h"
#include "argument_processor_main.h"

// ---------------------------------------------------------------------

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_APP_NAME);
    std::string appVersion = std::string(WSJCPP_APP_VERSION);
    if (!wsjcpp::dir_exists(".wsjcpp")) {
        WsjcppCore::makeDir(".wsjcpp");
    }
    if (!wsjcpp::file_exists(".wsjcpp/.gitignore")) {
        WsjcppCore::writeFile(".wsjcpp/.gitignore", "logs/*\ncache/*\n");
    }
    std::string appLogPath = ".wsjcpp/logs";
    if (!wsjcpp::dir_exists(appLogPath)) {
        WsjcppCore::makeDir(appLogPath);
    }
    WsjcppLog::setPrefixLogFile("wsjcpp");
    WsjcppLog::setLogDirectory(".wsjcpp/logs");

    ArgumentProcessorMain *pMain = new ArgumentProcessorMain();
    WsjcppArguments prog(argc, argv, pMain);

    int nResult = prog.exec();
    if (nResult != 0) {
        // print help
        std::cout
            << "Try exec 'wsjcpp help' for more information"
            << std::endl
            << std::endl
        ;
    }
    return nResult;
}
