#include "argument_processor_dependencies.h"
#include <wsjcpp_package_manager.h>
#include <iostream>
#include <wsjcpp_core.h>

ArgumentProcessorInstall::ArgumentProcessorInstall() 
  : WSJCppArgumentProcessor("install", "Install a source package from any sources (will be install deps)") {
      TAG = "ArgumentProcessorInstall";
    registryExample("from github source `./wsjcpp install 'https://github.com/wsjcpp/json:v3.7.0'`");
    registryExample("from github source `./wsjcpp install 'https://github.com/wsjcpp/json:develop'`");
    registryExample("from local system `./wsjcpp install 'file:///usr/share/some_package'`");
    registryExample("from http(s) `./wsjcpp install 'https://sea-kg.com/wsjcpp/example/latest'`");
    registryExample("from http(s) `./wsjcpp install 'https://sea-kg.com/wsjcpp/example/v3.0.0'`");
}

int ArgumentProcessorInstall::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg(".");
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    if (vSubParams.size() != 1) {
        WSJCppLog::err(TAG, "Expected url");
        // printHelp(vArgs);
        return -1;
    }

    std::string sPackage = vSubParams[0];
    WSJCppLog::info(TAG, "Try installing source package '" + sPackage + "' ...");
    if (pkg.install(sPackage)) {
        std::cout << "Installed." << std::endl;
        pkg.save();
    } else {
        WSJCppLog::err(TAG, "Could not install '" + sPackage + "' package.");
        return -1;
    }
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorReinstall::ArgumentProcessorReinstall() 
  : WSJCppArgumentProcessor("reinstall", "Reinstall a source package (will be replaced all sources)") {
      TAG = "ArgumentProcessorReinstall";
      registrySingleArgument("--all", "reinstall all");
      registryExample("from github source `wsjcpp reinstall 'https://github.com/wsjcpp/json:develop'`");
      registryExample("reintall by name package `wsjcpp reinstall wsjcpp-core`");
      registryExample("reinstall all packages `wsjcpp reinstall --all`");
      m_bReinstallAll = false;
}

bool ArgumentProcessorReinstall::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--all") {
        m_bReinstallAll = true;
        return true;
    }
    return false;
}

int ArgumentProcessorReinstall::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg(".");
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    if (vSubParams.size() != 1 && !m_bReinstallAll) {
        WSJCppLog::err(TAG, "Expected url");
        // printHelp(vArgs);
        return -1;
    }

    if (vSubParams.size() != 0 && m_bReinstallAll) {
        WSJCppLog::err(TAG, "Don't need params");
        // printHelp(vArgs);
        return -1;
    }
    if (m_bReinstallAll) {
        std::vector<WSJCppPackageManagerDependence> deps = pkg.getListOfDependencies();
        for (int i = 0; i < deps.size(); i++) {
            WSJCppPackageManagerDependence dep = deps[i];
            std::string sPackage = dep.getUrl();
            WSJCppLog::info(TAG, "Reinstall package '" + sPackage + "' ...");
            if (pkg.reinstall(sPackage)) {
                std::cout << "Reinstalled." << std::endl;
                pkg.save();
            } else {
                WSJCppLog::warn(TAG, "Could not reinstall '" + sPackage + "' package.");
            }
        }
    } else {
        std::string sPackage = vSubParams[0];
        std::vector<WSJCppPackageManagerDependence> deps = pkg.getListOfDependencies();
        for (int i = 0; i < deps.size(); i++) {
            WSJCppPackageManagerDependence dep = deps[i];
            if (sPackage == dep.getUrl() || sPackage == dep.getName()) {
                sPackage = dep.getUrl();
            }
        }
        WSJCppLog::info(TAG, "Try reinstalling '" + sPackage + "' package...");
        if (pkg.reinstall(sPackage)) {
            std::cout << "Reinstalled." << std::endl;
            pkg.save();
        } else {
            WSJCppLog::err(TAG, "Could not reinstall '" + sPackage + "' package.");
            return -1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorUninstall::ArgumentProcessorUninstall() 
  : WSJCppArgumentProcessor("uninstall", "Uninstall source package (!will be removed sources)") {
      TAG = "ArgumentProcessorUninstall";
      registryExample("uninstall by full url `./wsjcpp uninstall 'https://github.com/wsjcpp/json:develop'`");
      registryExample("uninstall by name `./wsjcpp uninstall 'nlohmann/json'`");
}

int ArgumentProcessorUninstall::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg(".");
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }
    
    if (vSubParams.size() != 1) {
        WSJCppLog::err(TAG, "Expected url");
        // printHelp(vArgs);
        return -1;
    }

    std::string sPackage = vSubParams[0];
    WSJCppLog::info(TAG, "Try uninstalling source package '" + sPackage + "' ...");
    if (pkg.uninstall(sPackage)) {
        std::cout << "Uninstalled." << std::endl;
        pkg.save();
    } else {
        WSJCppLog::err(TAG, "Could not uninstall '" + sPackage + "' package.");
        return -1;
    }
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorList::ArgumentProcessorList() 
  : WSJCppArgumentProcessor("list", "Show list of dependencies") {
      TAG = "ArgumentProcessorList";
      registrySingleArgument("--tree", "Tree");
      registryExample("from github source `./wsjcpp list");
      registryExample("from github source `./wsjcpp list --tree`");
      m_bTree = false;
}

bool ArgumentProcessorList::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--tree") {
        m_bTree = true;
        return true;
    }
    return false;
}

int ArgumentProcessorList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg(".");
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    if (vSubParams.size() != 0) {
        WSJCppLog::err(TAG, "No expected parameters");
        return -1;
    }
    std::string sResult = "";
    
    std::vector<WSJCppPackageManagerDependence> deps = pkg.getListOfDependencies();
    for (int i = 0; i < deps.size(); i++) {
        WSJCppPackageManagerDependence dep = deps[i];
        sResult += ""
            "* '" + dep.getName() + ":" + dep.getVersion() + "' (" + dep.getUrl() + " -> " + dep.getInstallationDir() + ")\r\n";
        if (m_bTree) {
            sResult += loadDependencies(pkg, dep, "|-- ");
        }
    }
    WSJCppLog::info(TAG, "\r\nDependencies: \r\n" + sResult);
    return 0;
}

std::string ArgumentProcessorList::loadDependencies(
    const WSJCppPackageManager &rootPackage, 
    const WSJCppPackageManagerDependence &mainDep,
    const std::string &sIntent
) {
    std::string sRet = "";
    std::string sInstallationDir = mainDep.getInstallationDir();
    WSJCppPackageManager m(sInstallationDir, rootPackage.getDir(), true);
    if (m.load()) {
        std::vector<WSJCppPackageManagerDependence> deps = m.getListOfDependencies();
        for (int i = 0; i < deps.size(); i++) {
            WSJCppPackageManagerDependence dep = deps[i];
            sRet += sIntent + " * '" + dep.getName() + ":" + dep.getVersion() + "' (" + dep.getUrl() + " -> " + dep.getInstallationDir() + ")\r\n";
            sRet += loadDependencies(rootPackage, dep, "   " + sIntent);
        }
    } else {
        WSJCppLog::err(TAG, "Could not load package");
    }
    return sRet;
}

// ---------------------------------------------------------------------

ArgumentProcessorUpdate::ArgumentProcessorUpdate() 
  : WSJCppArgumentProcessor("update", "Update all auto-generated files") {
      TAG = "ArgumentProcessorUpdate";
}

int ArgumentProcessorUpdate::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg(".");
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    if (vSubParams.size() != 0) {
        WSJCppLog::err(TAG, "No expected parameters");
        return -1;
    }

    pkg.updateAutogeneratedFiles();
    return 0;
}

// ---------------------------------------------------------------------
