
#include "argument_processor_resources.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>
#include <wsjcpp_hashes.h>
#include <sys/types.h>
#include <sys/stat.h>

// ---------------------------------------------------------------------
// ArgumentProcessorResources

ArgumentProcessorResources::ArgumentProcessorResources() 
: WsjcppArgumentProcessor({"resources", "res"}, "Pack files to c++ code", "Pack files to c++ code") {
    TAG = "ArgumentProcessorResources";
    // registrySingleArgument("--single", "What exactly do this single param?");
    // registryParameterArgument("-param", "What need this param?");
    // registryExample("here example of command");
    registryProcessor(new ArgumentProcessorResourcesList());
    registryProcessor(new ArgumentProcessorResourcesAdd());
    registryProcessor(new ArgumentProcessorResourcesRemove());
    registryProcessor(new ArgumentProcessorResourcesUpdate());
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

int ArgumentProcessorResources::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppLog::err(TAG, "Not implemented");
    return -1; 
}

// ---------------------------------------------------------------------
// ArgumentProcessorResourcesList

ArgumentProcessorResourcesList::ArgumentProcessorResourcesList() 
: WsjcppArgumentProcessor({"list", "ls"}, "List of pack files", "List of pack files") {
    TAG = "ArgumentProcessorResourcesList";
    registrySingleArgument("--more", "More information about resource file");
    m_bMore = false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorResourcesList::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--more") {
        m_bMore = true;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorResourcesList::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
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
    std::vector<WsjcppPackageManagerResourceFile> vList = pkg.getListOfResourceFiles();
    
    if (vList.size() == 0) {
        std::cout
            << "resource not found. "
            << std::endl
            << std::endl
            << "   For add please use a command: "
            << "   " << vRoutes[0] << " resources add <path>"
            << std::endl
            << std::endl;
    } else {
        std::cout 
            << std::endl
            << "resources: "
            << std::endl;
        for (int i = 0; i < vList.size(); i++) {
            WsjcppPackageManagerResourceFile resFile = vList[i];
            // TODO check exists / size / modified / sha1 
            if (!m_bMore) {
                std::cout << " - " << resFile.getFilepath() << " (size: " << resFile.getFilesize() << " bytes)" << std::endl;
            } else {
                std::cout
                    << "  - filepath: " << resFile.getFilepath()
                    << std::endl
                    << "    filesize: " << resFile.getFilesize()
                    << std::endl
                    << "    pack-as: " << resFile.getPackAs()
                    << std::endl
                    << "    sha1: " << resFile.getSha1()
                    << std::endl
                    << "    modified: " << WsjcppCore::formatTimeUTC(resFile.getModified())
                    << std::endl
                ;
            }
        }
        std::cout
            << std::endl;
    }
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorResourcesRemove

ArgumentProcessorResourcesRemove::ArgumentProcessorResourcesRemove() 
: WsjcppArgumentProcessor({"remove", "rm"}, "Remove resource", "Remove resource (only c++ code, original file will be not touched)") {
    TAG = "ArgumentProcessorResourcesRemove";
}

// ---------------------------------------------------------------------

int ArgumentProcessorResourcesRemove::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
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
    
    if (vSubParams.size() != 1) {
        std::cout 
            << std::endl
            << "ERROR: Expected arg1 with path to file" 
            << std::endl
            << std::endl;
        return -1;
    }
    std::string sFilepath = vSubParams[0];

    if (pkg.removeResource(sFilepath)) {
        pkg.updateAutogeneratedFiles();
        pkg.save();
        return 0;
    }
    return -1;
}

// ---------------------------------------------------------------------
// ArgumentProcessorResourcesAdd

ArgumentProcessorResourcesAdd::ArgumentProcessorResourcesAdd() 
: WsjcppArgumentProcessor({"add"}, "Pack files to c++ code", "Pack files to c++ code") {
    TAG = "ArgumentProcessorResourcesAdd";
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

int ArgumentProcessorResourcesAdd::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
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

    // TODO move to WsjcppManager
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

    sFilepath = WsjcppCore::doNormalizePath(sFilepath);
    if (pkg.hasResource(sFilepath)) {
        std::cout 
            << std::endl
            << "Resource '" << sFilepath << "' already exists" << std::endl
            << std::endl
            << "For remove this resource you can try call " << std::endl << "     wsjcpp res rm '" << sFilepath << "'" << std::endl
            << std::endl
            << "For update content of this resource " << std::endl << "     wsjcpp res up '" << sFilepath << "'" << std::endl
            << std::endl
            << std::endl
        ;
        return -1;
    }

    if (pkg.addResource(sFilepath, m_bText ? "text" : "binary")) {
        pkg.save();
        pkg.updateAutogeneratedFiles();
        return 0;
    }

    std::cout 
        << std::endl
        << "ERROR: Could not generate file resources"
        << std::endl
        << std::endl
    ;
    return -1;
}


// ---------------------------------------------------------------------
// ArgumentProcessorResourcesUpdate

ArgumentProcessorResourcesUpdate::ArgumentProcessorResourcesUpdate() 
: WsjcppArgumentProcessor({"update", "up"}, "Will update all resources", "Will be regenerated all resources") {
    TAG = "ArgumentProcessorResourcesUpdate";

}

// ---------------------------------------------------------------------

bool ArgumentProcessorResourcesUpdate::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorResourcesUpdate::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    /*if (vSubParams.size() != 1) {
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
    sFilepath = WsjcppCore::doNormalizePath(sFilepath);
    if (pkg.addResource(sFilepath, m_bText ? "text" : "binary")) {
        pkg.save();
        pkg.updateAutogeneratedFiles();
        return 0;
    }

    std::cout 
        << std::endl
        << "ERROR: Could not generate file resources"
        << std::endl
        << std::endl
    ;*/
    return -1;
}