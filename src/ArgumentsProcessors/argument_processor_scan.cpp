
#include "argument_processor_scan.h"
#include <wsjcpp_core.h>
#include <regex>

// ---------------------------------------------------------------------
// ArgumentProcessorScan

ArgumentProcessorScan::ArgumentProcessorScan() 
: WsjcppArgumentProcessor({"scan"}, "Scan the code", "Scan the code") {
    TAG = "ArgumentProcessorScan";
    registryProcessor(new ArgumentProcessorScanTodo());
    // registrySingleArgument("--single", "What exactly do this single param?");
    // registryParameterArgument("-param", "What need this param?");
    // registryExample("here example of command");
    
}

// ---------------------------------------------------------------------

bool ArgumentProcessorScan::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    WsjcppLog::err(TAG, "Not implemented");
    return false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorScan::applyParameterArgument(
    const std::string &sProgramName, 
    const std::string &sArgumentName, 
    const std::string &sValue
) {
    WsjcppLog::err(TAG, "Not implemented");
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorScan::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppLog::err(TAG, "Not implemented");
    return -1; 
}

// ---------------------------------------------------------------------
// ArgumentProcessorScanTodo

ArgumentProcessorScanTodo::ArgumentProcessorScanTodo() 
: WsjcppArgumentProcessor({"todo"}, "Search in code all TODOs", "Search in code all TODOs") {
      
}

// ---------------------------------------------------------------------

int ArgumentProcessorScanTodo::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    
    std::vector<std::string> vFoundFiles;

    // TODO directories must be configured
    // TODO move to wsjcpp-tree-walker
    std::vector<std::string> vScanDirs;
    vScanDirs.push_back("./src");
    vScanDirs.push_back("./src.wsjcpp");
    while(vScanDirs.size() > 0) {
        std::string sDir = vScanDirs[vScanDirs.size() - 1];
        vScanDirs.pop_back();
        std::vector<std::string> vDirs = WsjcppCore::listOfDirs(sDir);
        for (int i = 0; i < vDirs.size(); i++) {
            std::string sNewDir = sDir + "/" + vDirs[i];
            sNewDir = WsjcppCore::doNormalizePath(sNewDir);
            vScanDirs.push_back(sNewDir);
        }

        std::vector<std::string> vFiles = WsjcppCore::listOfFiles(sDir);
        for (int i = 0; i < vFiles.size(); i++) {
            vFoundFiles.push_back(WsjcppCore::doNormalizePath(sDir + "/" + vFiles[i]));
        }
    }

    std::regex rxTodo(".*//[ ]{0,}TODO.*");
    int nCount = 0;
    for (int i = 0; i < vFoundFiles.size(); i++) {
        std::string sFileName = vFoundFiles[i];
        std::string sExt = sFileName.substr(sFileName.find_last_of(".") + 1);
        if (sExt == "h" || sExt == "cpp" || sExt == "hpp" || sExt == "c") {
            // WsjcppLog::info(TAG, vFoundFiles[i]);
            std::string sFileContent;
            WsjcppCore::readTextFile(sFileName, sFileContent);
            std::vector<std::string> vLines = WsjcppCore::split(sFileContent, "\n");
            for (int n = 0; n < vLines.size(); n++) {
                std::string sLine = vLines[n];
                sLine = WsjcppCore::trim(sLine);
                if (std::regex_match(sLine, rxTodo)) {
                    nCount++;
                    std::cout << "Place: " << sFileName << ":" << (n+1) << std::endl
                        << "  Line: " << sLine << std::endl;
                }
            }
        }
    }
    std::cout << "Found todo: " << nCount << " times" << std::endl;
    return 0;
}