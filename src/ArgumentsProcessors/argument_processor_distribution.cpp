#include "argument_processor_distribution.h"
#include <wsjcpp_package_manager.h>
#include <wsjcpp_core.h>
#include <wsjcpp_hashes.h>

// ---------------------------------------------------------------------
// ArgumentProcessorDistribution

ArgumentProcessorDistribution::ArgumentProcessorDistribution() 
  : WsjcppArgumentProcessor({"distribution", "dist"}, "Distribution files from this source package", "Files which will distribute with current source package") {
      registryProcessor(new ArgumentProcessorDistributionList());
      registryProcessor(new ArgumentProcessorDistributionAdd());
      registryProcessor(new ArgumentProcessorDistributionRemove());
}

// ---------------------------------------------------------------------
// ArgumentProcessorDistributionList

ArgumentProcessorDistributionList::ArgumentProcessorDistributionList() 
  : WsjcppArgumentProcessor({"list", "ls"}, "Distribution list files", "Distribution list files") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorDistributionList::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
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
    std::cout << std::endl << "Distribution list:" << std::endl;
    std::vector<WsjcppPackageManagerDistributionFile> files = pkg.getListOfDistributionFiles();
    
    for (int i = 0; i < files.size(); i++) {
        std::cout << "    - ";
        WsjcppPackageManagerDistributionFile file = files[i];
        if (!WsjcppCore::fileExists(file.getSourceFile())) {
            std::cout << "[did not exists]";
        }
        std::cout <<  file.getType() << ": '" 
            << file.getSourceFile() << "' -> '" << file.getTargetFile() << std::endl;
    }
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorDistributionAdd

ArgumentProcessorDistributionAdd::ArgumentProcessorDistributionAdd() 
  : WsjcppArgumentProcessor({"add"}, "Add distribution file", "Add file to distribution list") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorDistributionAdd::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        WsjcppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    std::vector<std::pair<std::string,std::string>> vDistFiles;

    std::string sSourceFile = "";
    std::string sTargetFile = "";

    if (vSubParams.size() == 1) {
        sSourceFile = vSubParams[0];
        sTargetFile = WsjcppCore::extractFilename(vSubParams[0]);
    } else if (vSubParams.size() == 2) {
        sSourceFile = vSubParams[0];
        sTargetFile = vSubParams[1];
        // test '../' or './'
        std::string sTargetFile2 = WsjcppCore::doNormalizePath(pkg.getDir() + "/" + sTargetFile);
        if (sTargetFile2.rfind(pkg.getDir(), 0) != 0) {
            WsjcppLog::err(TAG, "Could not use upper directories for distribution files target path");
            return -1;
        }
    } else {
        WsjcppLog::err(TAG, "Expected params <source-file>");
        // printHelp(vArgs);
        return -1;
    }

    if (WsjcppCore::fileExists(sSourceFile)) {
        vDistFiles.push_back(std::pair<std::string,std::string>(sSourceFile, sTargetFile));
    } else if (WsjcppCore::dirExists(sSourceFile)) {
        std::vector<std::string> vSearchInDirs;
        vSearchInDirs.push_back(sSourceFile);
        while (vSearchInDirs.size() > 0) {
            std::string sDir = vSearchInDirs.back();
            vSearchInDirs.pop_back();
            std::vector<std::string> vDirs = WsjcppCore::getListOfDirs(sDir);
            for (int i = 0; i < vDirs.size(); i++) {
                vSearchInDirs.push_back(WsjcppCore::doNormalizePath(sDir + "/" + vDirs[i]));
            }
            std::vector<std::string> vFiles = WsjcppCore::getListOfFiles(sDir);
            for (int i = 0; i < vFiles.size(); i++) {
                std::string sFilepath = WsjcppCore::doNormalizePath(sDir + "/" + vFiles[i]);
                std::string sExtractFilename = WsjcppCore::extractFilename(sFilepath);
                vDistFiles.push_back(std::pair<std::string,std::string>(sFilepath, sExtractFilename));
            }
        }
    }
    
    if (vDistFiles.size() == 0) {
        WsjcppLog::err(TAG, "Not found files for distribution in '" + sSourceFile + "'");
        return -1;
    }

    int nCounterFilesAdded = 0; 
    for (int i = 0; i < vDistFiles.size(); i++) {
        sSourceFile = vDistFiles[i].first;
        sTargetFile = vDistFiles[i].second;
        std::string sFileExt = sSourceFile.substr(sSourceFile.find_last_of(".") + 1);
        sFileExt = WsjcppCore::toLower(sFileExt);
        std::string sFileType = "";

        if (sFileExt == "h" || sFileExt == "cpp" || sFileExt == "hpp" || sFileExt == "c") {
            sFileType = "source-code";
        } else if (sFileExt == "wsjcpp-script") {
            sFileType = "safe-scripting-generate";
        } else if (vDistFiles.size() == 1) {
            WsjcppLog::err(TAG, "Unknown extension '" + sFileExt + "' for file '" + sSourceFile + "'");
            // printHelp(vArgs);
            return -1;
        } else {
            // warn
            std::cout << " - file '" << sSourceFile << "' has unknown extension '" << sFileExt << "' - skipped" << std::endl;
            continue;
        }

        if (pkg.addSourceFile(sSourceFile, sTargetFile, sFileType)) {
            nCounterFilesAdded++;
            std::cout << "Added." << std::endl;
        } else {
            WsjcppLog::err(TAG, "Could not add file '" + sSourceFile + "' to package.");
            if (vDistFiles.size() == 1) {
                return -1;
            }
            
        }
    }
    if (nCounterFilesAdded > 0) {
        pkg.save();
        std::cout << "Updated wsjcpp.yml" << std::endl;
    }
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorDistributionRemove

ArgumentProcessorDistributionRemove::ArgumentProcessorDistributionRemove() 
  : WsjcppArgumentProcessor({"remove", "rm"}, "Remove distribution file", "Remove file from distribution list") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorDistributionRemove::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
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