#include "argument_processor_distribution.h"
#include <wsjcpp_package_manager.h>
#include <wsjcpp_core.h>
#include <wsjcpp_hashes.h>

ArgumentProcessorDistribution::ArgumentProcessorDistribution() 
  : WsjcppArgumentProcessor({"distribution", "dist"}, "Files which will distribute with current source package") {
      registryProcessor(new ArgumentProcessorDistributionList());
      registryProcessor(new ArgumentProcessorDistributionAdd());
      registryProcessor(new ArgumentProcessorDistributionRemove());
      registryProcessor(new ArgumentProcessorDistributionUpdate());
}

// ---------------------------------------------------------------------

ArgumentProcessorDistributionList::ArgumentProcessorDistributionList() 
  : WsjcppArgumentProcessor({"list", "ls"}, "Distribution list files") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorDistributionList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        WsjcppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    if (vSubParams.size() != 0) {
        WsjcppLog::err(TAG, "No expected params");
        // printHelp(vArgs);
        return -1;
    }
    std::string sList = "\r\nDistribution list:\r\n";
    std::vector<WsjcppPackageManagerDistributionFile> files = pkg.getListOfDistributionFiles();
    
    for (int i = 0; i < files.size(); i++) {
        WsjcppPackageManagerDistributionFile file = files[i];
        sList += "   ";
        if (!WsjcppCore::fileExists(file.getSourceFile())) {
            WsjcppLog::err(TAG, "File did not exists '" + file.getSourceFile() + "'");
            sList += "[did not exists] ";
        } else {
            std::string sContent;
            if (WsjcppCore::readTextFile(file.getSourceFile(), sContent)) {
                std::string sSha1 = WsjcppHashes::sha1_calc_hex(sContent);
                if (sSha1 != file.getSha1()) {
                    sList += "[wrong sha1] ";
                    WsjcppLog::warn(TAG, "Did not match sha1 for file '" + file.getSourceFile() + "'. expected '" + sSha1 + "', but got '" + file.getSha1() + "'");
                }
            }
        }
        sList += 
            file.getType() + ": '" 
            + file.getSourceFile() 
            + "' -> '"
            + file.getTargetFile()
            + "' (sha1: " + file.getSha1() + ")" + "\r\n";
    }
    WsjcppLog::info(TAG, sList);
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorDistributionAdd::ArgumentProcessorDistributionAdd() 
  : WsjcppArgumentProcessor({"add"}, "Add file to distribution list") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorDistributionAdd::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        WsjcppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }
    std::string sSourceFile = "";
    std::string sTargetFile = "";

    if (vSubParams.size() == 1) {
        sSourceFile = vSubParams[0];
        sTargetFile = WsjcppCore::extractFilename(vSubParams[0]);
    } else if (vSubParams.size() == 2) {
        sSourceFile = vSubParams[0];
        sTargetFile = vSubParams[1]; // TODO check '../' or './'
    } else {
        WsjcppLog::err(TAG, "Expected params <source-file>");
        // printHelp(vArgs);
        return -1;
    }

    if (pkg.addSourceFile(sSourceFile, sTargetFile, "source-code")) {
        std::cout << "Added." << std::endl;
        pkg.save();
    } else {
        WsjcppLog::err(TAG, "Could not add file '" + sSourceFile + "' to package.");
        return -1;
    }
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorDistributionRemove::ArgumentProcessorDistributionRemove() 
  : WsjcppArgumentProcessor({"remove"}, "Remove file from distribution list") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorDistributionRemove::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        WsjcppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }
    std::string sSourceFile = "";

    if (vSubParams.size() == 1) {
        sSourceFile = vSubParams[0];
    } else {
        WsjcppLog::err(TAG, "Expected params <source-file>");
        // printHelp(vArgs);
        return -1;
    }

    if (pkg.removeSourceFile(sSourceFile)) {
        std::cout << "Removed." << std::endl;
        pkg.save();
    } else {
        WsjcppLog::err(TAG, "Could not remove file '" + sSourceFile + "' to package.");
        return -1;
    }
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorDistributionUpdate::ArgumentProcessorDistributionUpdate() 
  : WsjcppArgumentProcessor({"update"}, "Update sha1 in distribution list") {
      registrySingleArgument("--all", "update sha1 in all");
      registryExample("from github source `./wsjcpp distribution update src/module.cpp`");
      registryExample("from github source `./wsjcpp distribution update --all`");
      m_bUpdateAll = false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorDistributionUpdate::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--all") {
        m_bUpdateAll = true;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorDistributionUpdate::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        WsjcppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }
    std::string sSourceFile = "";
    if (m_bUpdateAll && vSubParams.size() == 0) {
        std::vector<WsjcppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
        int nCounter = 0;
        for (int i = 0; i < vFiles.size(); i++) {
            WsjcppPackageManagerDistributionFile file = vFiles[i];
            if (pkg.updateSourceFile(file.getSourceFile())) {
                nCounter++;
            }
        }
        if (nCounter > 0) {
            pkg.save();
            std::cout << "Updated." << std::endl;
        }
    } else if (!m_bUpdateAll && vSubParams.size() == 1) {
        sSourceFile = vSubParams[0];
        if (pkg.updateSourceFile(sSourceFile)) {
            pkg.save();
            std::cout << "Updated." << std::endl;
        } else {
            WsjcppLog::err(TAG, "Could not update source-file '" + sSourceFile + "'");
            // printHelp(vArgs);
            return -1;
        }
    } else {
        WsjcppLog::err(TAG, "Expected params <source-file> or --all");
        return -1;
    }
    return 0;
}

// ---------------------------------------------------------------------