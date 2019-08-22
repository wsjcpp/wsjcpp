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

    helpArgs.addHelp("new", "n", FallenParseArgType::PARAMETER, "New a source package %DIRECTORY% (cppspm.json file)");
    // helpArgs.addHelp("create-empty-project", "cep", FallenParseArgType::PARAMETER, "Prepare empty cmake project in %DIRECTORY%");
    // helpArgs.addHelp("update-deps", "ud", FallenParseArgType::SINGLE_OPTION, "Update dependencies and src.cppspm/CMakeList.txt");
    helpArgs.addHelp("dependencies", "d", FallenParseArgType::SINGLE_OPTION, "Show dependencies like a tree");
    // helpArgs.addHelp("search", "s", FallenParseArgType::PARAMETER, "Search a source package by name or keywords");
    // helpArgs.addHelp("update", "u", FallenParseArgType::PARAMETER, "Install a source package like 'some_package:0.0.1'");
    // helpArgs.addHelp("install", "i", FallenParseArgType::PARAMETER, "Install a source package like 'some_package:0.0.1'");
    // helpArgs.addHelp("install-from-local", "ilo", FallenParseArgType::PARAMETER, "Install a source package from a link '/home/users/cppspm/packages'");
    helpArgs.addHelp("install-from-github", "igh", FallenParseArgType::PARAMETER, "Install a source package from github, example 'user/repo_name:v0.0.1'");
    // helpArgs.addHelp("install-via-link", "il", FallenParseArgType::PARAMETER, "Install a source package from a link 'http://your-site.com/cppspm/some_package-v1.0.0.zip'");
    // helpArgs.addHelp("uninstall", "un", FallenParseArgType::PARAMETER, "Uninstall package 'some_package'");
    helpArgs.addHelp("files", "f", FallenParseArgType::SINGLE_OPTION, "Show list of files in source package");
    helpArgs.addHelp("add-source-file", "asf", FallenParseArgType::PARAMETER, "Add source file to source package");
    helpArgs.addHelp("delete-source-file", "dsf", FallenParseArgType::PARAMETER, "Delete source file from source package (from cppspm.json)");
    helpArgs.addHelp("servers", "s", FallenParseArgType::SINGLE_OPTION, "List of servers");
    helpArgs.addHelp("add-remote-server", "as", FallenParseArgType::PARAMETER, "Add server to source package");
    helpArgs.addHelp("delete-remote-server", "ds", FallenParseArgType::PARAMETER, "Delete server from source package");

    helpArgs.addHelp("verify", "vf", FallenParseArgType::SINGLE_OPTION, "Verify files / sums / format / configs etc..");
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
    } /* else if (helpArgs.has("update-deps")) {
        CppSPM::Manager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        pkg.updateDependencies();
        return 0;
    } */ else if (helpArgs.has("dependencies")) {
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
    }  else if (helpArgs.has("add-source-file")) {
        CppSPM::Manager pkg(".");
        std::string sFile = helpArgs.option("add-source-file");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.addFile(sFile)) {
            pkg.save();
        }
        return 0;
    } else if (helpArgs.has("delete-source-file")) {
        CppSPM::Manager pkg(".");
        std::string sFile = helpArgs.option("delete-source-file");
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
    }  else if (helpArgs.has("add-remote-server")) {
        CppSPM::Manager pkg(".");
        std::string sServer = helpArgs.option("add-remote-server");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.addServer(sServer)) {
            pkg.save();
        }
        return 0;
    } else if (helpArgs.has("delete-remote-server")) {
        CppSPM::Manager pkg(".");
        std::string sServer = helpArgs.option("delete-remote-server");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.deleteServer(sServer)) {
            pkg.save();
        }
        return 0;
    } else if (helpArgs.has("verify")) {
        CppSPM::Manager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        pkg.verify();
        return 0;
    } else if (helpArgs.has("install-from-github")) {
        CppSPM::Manager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        std::string sPackageName = helpArgs.option("install-from-github");
        std::cout << "Try installing source package " << sPackageName << " ..." << std::endl;
        if (pkg.installFromGithub(sPackageName)) {
            std::cout << "Installed." << std::endl;
            pkg.save();
        }
        return 0;
    } else {
        helpArgs.printHelp();
    }

    return 0;
}
