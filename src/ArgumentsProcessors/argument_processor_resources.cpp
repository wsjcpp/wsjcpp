
#include "argument_processor_resources.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>

// ---------------------------------------------------------------------
// ArgumentProcessorResources

ArgumentProcessorResources::ArgumentProcessorResources() 
: WsjcppArgumentProcessor({"resources", "res"}, "Pack files to c++ code") {
    TAG = "ArgumentProcessorResources";
    // registrySingleArgument("--single", "What exactly do this single param?");
    // registryParameterArgument("-param", "What need this param?");
    // registryExample("here example of command");
    registryProcessor(new ArgumentProcessorResourcesAdd());
}

// ---------------------------------------------------------------------

bool ArgumentProcessorResources::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    WsjcppLog::err(TAG, "Not implemented");
    return false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorResources::applyParameterArgument(
    const std::string &sProgramName, 
    const std::string &sArgumentName, 
    const std::string &sValue
) {
    WsjcppLog::err(TAG, "Not implemented");
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorResources::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppLog::err(TAG, "Not implemented");
    return -1; 
}

// ---------------------------------------------------------------------
// ArgumentProcessorResourcesAdd

ArgumentProcessorResourcesAdd::ArgumentProcessorResourcesAdd() 
: WsjcppArgumentProcessor({"add"}, "Pack files to c++ code") {
    TAG = "ArgumentProcessorResources";
    registrySingleArgument("--text", "Pack resources like text");
    registrySingleArgument("--binary", "Pack resources like binary");
    m_bText = false;
    m_bBinary = false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorResourcesAdd::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--text") {
        m_bText = true;
        return true;
    }
    if (sArgumentName == "--binary") {
        m_bBinary = true;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorResourcesAdd::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    if (vSubParams.size() != 1) {
        std::cout 
            << std::endl
            << "ERROR: Expected arg1 with path to file" 
            << std::endl
            << std::endl;
        return -1;
    }
    std::string sFilepath = vSubParams[0];

    if (!WsjcppCore::fileExists(sFilepath)) {
        std::cout 
            << std::endl
            << "ERROR: '" << sFilepath << "' - file not exists" 
            << std::endl
            << std::endl;
        return -1; 
    }

    std::string sFileExt = sFilepath.substr(sFilepath.find_last_of(".") + 1);
    sFileExt = WsjcppCore::toLower(sFileExt);

    if (!m_bText && !m_bBinary) {
        // if user not specified
        if (sFileExt == "svg" 
            || sFileExt == "js" 
            || sFileExt == "css"
            || sFileExt == "html"
            || sFileExt == "conf"
            || sFileExt == "sh"
        ) {
            m_bText = true;
        } else {
            m_bBinary = true;
        }
    }

    if (m_bText && m_bBinary) {
        std::cout 
            << std::endl
            << "ERROR: File could not be and text and binary please specify only one"
            << std::endl
            << std::endl;
        return -1; 
    }

    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout 
            << std::endl
            << "ERROR: Could not load package info from current directory"
            << std::endl
            << std::endl
        ;
        return -1;
    }

    std::string sDirResources = "./src/resources.wsjcpp";
    if (!WsjcppCore::dirExists(sDirResources)) {
        WsjcppCore::makeDir(sDirResources);
    }

    return -1;
}