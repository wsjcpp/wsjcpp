#include <string.h>
#include <iostream>
#include <algorithm>
#include <fallen.h>
#include <fallen_parse_args.h>
#include "cppspm_manager.h"

// ---------------------------------------------------------------------

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(CPPSPM_NAME);
    std::string appVersion = std::string(CPPSPM_VERSION);

    FallenParseArgs helpArgs(argc, argv);
    helpArgs.setAppName(appName);
    helpArgs.setAppVersion(appVersion);

    helpArgs.addHelp("new", "n", FallenParseArgType::PARAMETER, "New a source package %DIRECTORY%");
    helpArgs.addHelp("update-deps", "ud", FallenParseArgType::SINGLE_OPTION, "Update dependencies and src.cppspm/CMakeList.txt");
    helpArgs.addHelp("dependencies", "d", FallenParseArgType::SINGLE_OPTION, "Show dependencies like a tree");
    // helpArgs.addHelp("search", "s", FallenParseArgType::PARAMETER, "Search a source package by name or keywords");
    // helpArgs.addHelp("update", "u", FallenParseArgType::PARAMETER, "Install a source package like 'some_package:0.0.1'");
    // helpArgs.addHelp("install", "i", FallenParseArgType::PARAMETER, "Install a source package like 'some_package:0.0.1'");
    // helpArgs.addHelp("install-via-github", "ig", FallenParseArgType::PARAMETER, "Install a source package from github, example 'some_package:0.0.1'");
    // helpArgs.addHelp("install-via-link", "il", FallenParseArgType::PARAMETER, "Install a source package from a link 'http://your-site.com/cppspm/some_package-v1.0.0.zip'");
    // helpArgs.addHelp("uninstall", "un", FallenParseArgType::PARAMETER, "Uninstall package 'some_package'");
    helpArgs.addHelp("files", "f", FallenParseArgType::SINGLE_OPTION, "Show list of files in source package");
    helpArgs.addHelp("add-file", "af", FallenParseArgType::PARAMETER, "Add new file to source package");
    helpArgs.addHelp("delete-file", "df", FallenParseArgType::PARAMETER, "Delete file from source package (from cppspm.json)");
    helpArgs.addHelp("servers", "s", FallenParseArgType::SINGLE_OPTION, "List of servers");
    helpArgs.addHelp("add-server", "as", FallenParseArgType::PARAMETER, "Add server to source package");
    helpArgs.addHelp("delete-server", "ds", FallenParseArgType::PARAMETER, "Delete server from source package");

    // helpArgs.addHelp("verify", "vf", FallenParseArgType::PARAMETER, "Verify files / sums / format / configs etc..");
    // helpArgs.addHelp("publish", "p", FallenParseArgType::PARAMETER, "Publish your package to server");
    
    if (helpArgs.handleDefault()) {
        return 0;
    } else if (helpArgs.has("new")) {
        std::string sCppSPMJson = "cppspm.json";
        std::string sDirectory = helpArgs.option("new");
        if (Fallen::fileExists(sCppSPMJson)) {
            std::cout << "Error: cppspm.json already exists." << std::endl;
            return -1;
        }
        CppSPM::Manager pkg(sDirectory);
        if (!pkg.init()) {
            return -1;
        }
        pkg.save();
        return 0;
    } else if (helpArgs.has("update-deps")) {
        CppSPM::Manager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        pkg.updateDependencies();
        return 0;
    } else if (helpArgs.has("dependencies")) {
        CppSPM::Manager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        pkg.printDependencies();
        return 0;
    } else if (helpArgs.has("files")) {
        CppSPM::Manager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        pkg.printFiles();
        return 0;
    }  else if (helpArgs.has("add-file")) {
        CppSPM::Manager pkg(".");
        std::string sFile = helpArgs.option("add-file");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.addFile(sFile)) {
            pkg.save();
        }
        return 0;
    } else if (helpArgs.has("delete-file")) {
        CppSPM::Manager pkg(".");
        std::string sFile = helpArgs.option("delete-file");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.deleteFile(sFile)) {
            pkg.save();
        }
        return 0;
    }  else if (helpArgs.has("servers")) {
        CppSPM::Manager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        pkg.printServers();
        return 0;
    }  else if (helpArgs.has("add-server")) {
        CppSPM::Manager pkg(".");
        std::string sServer = helpArgs.option("add-server");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.addServer(sServer)) {
            pkg.save();
        }
        return 0;
    } else if (helpArgs.has("delete-server")) {
        CppSPM::Manager pkg(".");
        std::string sServer = helpArgs.option("delete-server");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.deleteServer(sServer)) {
            pkg.save();
        }
        return 0;
    } else if (helpArgs.has("verify")) {
        std::string sDir = helpArgs.option("verify");
        return 0;
    } else {
        helpArgs.printHelp();
    }

    return 0;
}
