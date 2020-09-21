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
    
    std::string sFileExt = sSourceFile.substr(sSourceFile.find_last_of(".") + 1);
    sFileExt = WsjcppCore::toLower(sFileExt);
    std::string sFileType = "";

    if (sFileExt == "h" || sFileExt == "cpp" || sFileExt == "hpp" || sFileExt == "c") {
        sFileType = "source-code";
    } else if (sFileExt == "wsjcpp-script") {
        sFileType = "safe-scripting-generate";
    } else {
        WsjcppLog::err(TAG, "Unknown extension '" + sFileExt + "' for file '" + sSourceFile + "'");
        // printHelp(vArgs);
        return -1;
    }

    if (pkg.addSourceFile(sSourceFile, sTargetFile, sFileType)) {
        std::cout << "Added." << std::endl;
        pkg.save();
    } else {
        WsjcppLog::err(TAG, "Could not add file '" + sSourceFile + "' to package.");
        return -1;
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