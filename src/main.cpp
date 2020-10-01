#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include "wsjcpp_package_manager.h"
#include "argument_processor_main.h"

// ---------------------------------------------------------------------

void printHelp(std::vector<std::string> &vArgs) {
    std::string sProgramName = vArgs.size() > 0 ? vArgs[0] : "wsjcpp";
    std::cout << std::endl
    << "\t" << "authors" << std::endl
    << "\t\t" << "List of authors in current package" << std::endl
    << std::endl
    << "\t" << "authors tree" << std::endl
    << "\t\t" << "List of authors from all packages (tree recoursive)" << std::endl
    << std::endl
    << "\t" << "authors add 'Full Name' 'Author Email'" << std::endl
    << "\t\t" << "Add author to current packages" << std::endl
    << std::endl
    << "\t" << "authors rm 'Full Name <Author Email>'" << std::endl
    << "\t\t" << "Remove author from curernt package" << std::endl
    << std::endl
    << "\t\t" << "Generate some custom files/classes" << std::endl
    << std::endl;
}

// ---------------------------------------------------------------------

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_APP_NAME);
    std::string appVersion = std::string(WSJCPP_APP_VERSION);
    if (!WsjcppCore::dirExists(".wsjcpp")) {
        WsjcppCore::makeDir(".wsjcpp");
    }
    if (!WsjcppCore::fileExists(".wsjcpp/.gitignore")) {
        WsjcppCore::writeFile(".wsjcpp/.gitignore", "logs/*\ncache/*\n");
    }
    std::string appLogPath = ".wsjcpp/logs";
    if (!WsjcppCore::dirExists(appLogPath)) {
        WsjcppCore::makeDir(appLogPath);
    }
    WsjcppLog::setPrefixLogFile("wsjcpp");
    WsjcppLog::setLogDirectory(".wsjcpp/logs");

    ArgumentProcessorMain *pMain = new ArgumentProcessorMain();
    WsjcppArguments prog(argc, argv, pMain);

    std::vector<std::string> vArgs;
    for (int i = 0; i < argc; i++) {
        vArgs.push_back(std::string(argv[i]));
    }

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

    
    if (vArgs.size() > 1) {
   
        WsjcppPackageManager pkg(".");
        if (!pkg.load()) {
            std::cout << "Could not load package info from current directory" << std::endl;
            return -1;
        }

        if (vArgs[1] == "authors") {
            if (argc == 2) {
                pkg.printAuthors();
                return 0;
            }
            if (argc == 4 && vArgs[2] == "rm") {
                std::string sFullAuthorName = vArgs[3];
                if (pkg.removeAuthor(sFullAuthorName)) {
                    pkg.save();
                }
                return 0;
            }
            if (argc == 5 && vArgs[2] == "add") {
                std::string sAuthorName = vArgs[3];
                std::string sAuthorEmail = vArgs[4];
                if (pkg.addAuthor(sAuthorName, sAuthorEmail)) {
                    pkg.save();
                }
                return 0;
            }
            if (argc == 3 && vArgs[2] == "tree") {
                pkg.printAuthorsTree();
                return 0;
            }
            return -1;
        }
    }

    return 0;
}
