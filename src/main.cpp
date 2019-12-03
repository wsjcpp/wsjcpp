#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include "wsjcpp_package_manager.h" 

// ---------------------------------------------------------------------

void printHelp(std::vector<std::string> &vArgs) {
    std::string sProgramName = vArgs.size() > 0 ? vArgs[0] : "wsjcpp";
    std::cout << std::endl
    << " Usage: " << sProgramName << " <command> <params>" << std::endl << std::endl
    << " Commands: " << std::endl
    << std::endl
    << "\t" << "new <dir>" << std::endl
    << "\t\t" << "Prepare new package in dir" << std::endl
    << "\t\t" << "Will be generated build_simple / clean / wsjcpp.json / etc.. files README.md" << std::endl
    << "\t\t" << " - example: `" << sProgramName << " new .`" << std::endl
    << std::endl
    // "New a source package %DIRECTORY% (wsjcpp.json file)"
    << "\t" << "install <package-name>" << std::endl
    << "\t\t" << "Install a source package from any sources (will be install deps):" << std::endl
    << "\t\t" << " - example 1 from github source `" << sProgramName << " install 'https://github.com/sea-kg/nlohmann_json:v3.7.0'`" << std::endl
    << "\t\t" << " - example 2 from github source `" << sProgramName << " install 'https://github.com/sea-kg/nlohmann_json:master'`" << std::endl
    << "\t\t" << " - example 3 from local system `" << sProgramName << " install 'file:///usr/share/some_package'`" << std::endl
    << "\t\t" << " - example 4 from http(s) `" << sProgramName << " install 'https://sea-kg.com/wsjcpp/example/latest'`" << std::endl
    << "\t\t" << " - example 5 from http(s) `" << sProgramName << " install 'https://sea-kg.com/wsjcpp/example/v3.0.0'`" << std::endl
    << std::endl
    << "\t" << "requirements packages list - List of requirements a source packages " << std::endl
    << "\t\t" << " - example: `" << sProgramName << " requirements packages`" << std::endl
    << std::endl
    << "\t" << "uninstall <package-name>" << std::endl
    << std::endl
    << "\t" << "verify" << std::endl
    << "\t\t" << "Verify files / sums / format / configs etc.." << std::endl
    << std::endl
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
    << "\t" << "distribution sources list" << std::endl
    << "\t" << "distribution sources add <from-filepath> <to-filepath>" << std::endl
    << "\t" << "distribution sources rm <from-filepath>" << std::endl
    << std::endl
    << "\t" << "deps" << std::endl
    << "\t\t" << "Show dependencies" << std::endl
    << std::endl
    << "\t" << "run <process>" << std::endl
    << "\t" << "run clean - Do run clean.sh script" << std::endl
    << "\t" << "run build - Do run build_simple.sh script" << std::endl
    << "\t" << "run unit-tests - Build and run unit-tests" << std::endl
    << std::endl
    << "\t" << "unit-tests [params]" << std::endl
    << "\t" << "unit-tests create <some_test_name> - Create new some_test_name" << std::endl
    << "\t" << "unit-tests delete <some_test_name> - Delete some_test_name" << std::endl
    << "\t" << "unit-tests list - list of unit-tests" << std::endl
    << "\t" << "unit-tests files - files list of unit-tests" << std::endl
    << std::endl
    << "\t" << "generate" << std::endl
    << "\t" << "generate list" << std::endl
    << "\t" << "generate <name>" << std::endl
    << "\t\t" << "Generate some custom files/classes" << std::endl
    << std::endl
    << "\t" << "templates" << std::endl
    << "\t\t" << "Templates which distribute with current source package" << std::endl
    << "\t" << "templates list" << std::endl
    << "\t\t" << "List of defined templates" << std::endl
    << "\t" << "templates add <name> <script>" << std::endl
    << "\t\t" << "Add new template to 'wsjcpp.json'" << std::endl
    << "\t" << "templates rm <name>" << std::endl
    << "\t\t" << "Remove template from 'wsjcpp.json'" << std::endl
    << std::endl
    // << "\t" << "docs" << std::endl
    // << "\t" << "docs make" << std::endl
    // << "\t\t" << "Make documentation" << std::endl
    << std::endl;
}

// ---------------------------------------------------------------------

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    std::string appLogPath = ".wsjcpp-logs";
    if (!WSJCppCore::dirExists(appLogPath)) {
        WSJCppCore::makeDir(appLogPath);
    }
    WSJCppLog::setPrefixLogFile("wsjcpp");
    WSJCppLog::setLogDirectory(".wsjcpp-logs");
    WSJCppLog::info(TAG, "Hello");
    std::vector<std::string> vArgs;

    for (int i = 0; i < argc; i++) {
        vArgs.push_back(std::string(argv[i]));
    }

    if (vArgs.size() == 3 && vArgs[1] == "info") {
        WSJCppPackageManager pkg(vArgs[2]);
        if (!pkg.load()) {
            return -1;
        }
        pkg.printInfo();
        return 0;
    }
    
    if (vArgs.size() > 1) {
        if (vArgs[1] == "help") {
            printHelp(vArgs);
            return -1;
        }
        if (vArgs[1] == "new") {
            if (argc != 3) {
                printHelp(vArgs);
                return -1;
            }
            // TODO move inside WSJCppPackageManager.init
            std::string sDirectory = vArgs[2];
            std::string sWSJCppJson = sDirectory + "/wsjcpp.json";
            if (WSJCppCore::fileExists(sWSJCppJson)) {
                std::cout << "Error: wsjcpp.json already exists." << std::endl;
                return -1;
            }
            WSJCppPackageManager pkg(sDirectory);
            if (!pkg.init()) {
                return -1;
            }
            pkg.save();
            return 0;
        }

        WSJCppPackageManager pkg(".");
        if (!pkg.load()) {
            std::cout << "Could not load package info from current directory" << std::endl;
            return -1;
        }

        if (vArgs[1] == "packages" && argc == 2) {
            pkg.printPackages();
            return 0;
        } else if (vArgs[1] == "verify" && argc == 2) {
            pkg.verify();
            return 0;
        } else if (vArgs[1] == "authors") {
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
            printHelp(vArgs);
            return -1;
        } else if (vArgs[1] == "deps") {
            if (argc == 2) {
                pkg.printDependencies();
                return 0;
            }
            // TODO parse sub commands for fix-conflicts
        } else if (vArgs[1] == "distribution-files") {
            if (argc == 3 && vArgs[2] == "list") {
                pkg.printFiles();
                return 0;
            }
            
            if (argc == 4 && vArgs[2] == "rm") {
                std::string fromFile = vArgs[3];
                if (pkg.removeFile(fromFile)) {
                    pkg.save();
                }
                return 0;
            }

            if (argc == 5 && vArgs[2] == "add") {
                std::string fromFile = vArgs[3];
                std::string toFile = vArgs[4];
                if (pkg.addFile(fromFile, toFile)) {
                    pkg.save();
                }
                return 0;
            }

            printHelp(vArgs);
            return -1;
        } else if (vArgs[1] == "info") {
            if (argc == 2) {
                pkg.printInfo();
                return 0;
            }
            // TODO find some package and print info it
        } else if (vArgs[1] == "install") {
            if (argc != 3) {
                printHelp(vArgs);
                return -1;
            }
            std::string sPackage = vArgs[2];
            std::cout << "Try installing source package " << sPackage << " ..." << std::endl;
            if (pkg.install(sPackage)) {
                std::cout << "Installed." << std::endl;
                pkg.save();
            } else {
                std::cout << "Could not install this package." << std::endl;
                return -1;
            }
            return 0;

        }
    }
    printHelp(vArgs);
    return -1;
    
    // Will be copied to .wsjcpp-cache/package_name - this must be ignored
    
    // TODO if version already installed - you want replace version (y/N)?
    // TODO fix deps conflicts if used different versions
    // in 'dependencies' on first level must be added 'fix-conflict' - will replaced package version
    // like `wsjcpp fix-conflict 'for-some-package' 'package-with-conflict' 'package-to-fix-conflict'`
    // helpArgs.addHelp("install-via-link", "il", FallenParseArgType::PARAMETER, "Install a source package from a link 'http://your-site.com/cppspm/some_package-v1.0.0.zip'");
    // helpArgs.addHelp("uninstall", "un", FallenParseArgType::PARAMETER, "Uninstall package 'some_package'");
    
    // helpArgs.addHelp("add-remote-server", "as", FallenParseArgType::PARAMETER, "Add server to source package");
    // helpArgs.addHelp("delete-remote-server", "ds", FallenParseArgType::PARAMETER, "Delete server from source package");

    // must be 
    // files add 'from-filename' 'to-filename'
    // files rm 'from-filename' 
    // files list

    /*helpArgs.addHelp("verify", "vf", FallenParseArgType::SINGLE_OPTION, "");
    // helpArgs.addHelp("publish", "p", FallenParseArgType::PARAMETER, "Publish your package to server");
    
    if (helpArgs.handleDefault()) {
        return 0;
    } else if (helpArgs.has("files")) {
        WSJCppPackageManager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        
        return 0;
    }  else if (helpArgs.has("add-source-file")) {
        WSJCppPackageManager pkg(".");
        std::string sFile = helpArgs.option("add-source-file");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.addFile(sFile)) {
            pkg.save();
        }
        return 0;
    } else if (helpArgs.has("delete-source-file")) {
        WSJCppPackageManager pkg(".");
        std::string sFile = helpArgs.option("delete-source-file");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.deleteFile(sFile)) {
            pkg.save();
        }
        return 0;
    }  else if (helpArgs.has("servers")) {
        WSJCppPackageManager pkg(".");
        if (!pkg.load()) {
            return -1;
        }
        pkg.printServers();
        return 0;
    }  else if (helpArgs.has("add-remote-server")) {
        WSJCppPackageManager pkg(".");
        std::string sServer = helpArgs.option("add-remote-server");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.addServer(sServer)) {
            pkg.save();
        }
        return 0;
    } else if (helpArgs.has("delete-remote-server")) {
        WSJCppPackageManager pkg(".");
        std::string sServer = helpArgs.option("delete-remote-server");
        if (!pkg.load()) {
            return -1;
        }
        if (pkg.deleteServer(sServer)) {
            pkg.save();
        }
        return 0;
    } 
    */
    return 0;
}
