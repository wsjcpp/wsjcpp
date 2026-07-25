#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include "wsjcpp_package_manager.h"
#include "argument_processor_main.h"
#include "include/s5k_global.h"

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_APP_NAME);
    std::string appVersion = std::string(WSJCPP_APP_VERSION);
    if (!wsjcpp::dir_exists(s5k::global_defines::MAIN_APP_CACHE_DIR)) {
        WsjcppCore::makeDir(s5k::global_defines::MAIN_APP_CACHE_DIR);
    }
    if (!wsjcpp::file_exists(".wsjcpp/.gitignore")) {
        WsjcppCore::writeFile(".wsjcpp/.gitignore", "logs/*\ncache/*\n");
    }
    if (!wsjcpp::dir_exists(s5k::global_defines::MAIN_APP_LOG_DIR)) {
        WsjcppCore::makeDir(s5k::global_defines::MAIN_APP_LOG_DIR);
    }
    WsjcppLog::setPrefixLogFile("wsjcpp");
    WsjcppLog::setLogDirectory(".wsjcpp/logs");

    ArgumentProcessorMain *pMain = new ArgumentProcessorMain();
    WsjcppArguments prog(argc, argv, pMain);

    int res = prog.exec();
    if (res != 0) {
        // print help
        std::cout
            << "Try exec 'wsjcpp help' for more information"
            << std::endl
            << std::endl
        ;
    }
    return res;
}
