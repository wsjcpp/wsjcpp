#include "argument_processor_generate.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>

ArgumentProcessorGenerate::ArgumentProcessorGenerate() 
: WSJCppArgumentProcessor("generate", "Generate source code snippets/templates/examples") {
    registryProcessor(new ArgumentProcessorGenerateList());
    // registryProcessor(new ArgumentProcessorGenerateCreate());
    // registryProcessor(new ArgumentProcessorGenerateDelete());
}

// ---------------------------------------------------------------------

ArgumentProcessorGenerateList::ArgumentProcessorGenerateList() 
: WSJCppArgumentProcessor("list", "List of defined templates") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorGenerateList::exec(
    const std::string &sProgramName, 
    const std::vector<std::string> &vSubParams
) {

    WSJCppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    std::vector<WSJCppPackageManagerDistributionFile> vScripts;
    std::vector<WSJCppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
    for (int i = 0; i < vFiles.size(); i++) {
        WSJCppPackageManagerDistributionFile file = vFiles[i];
        // WSJCppLog::warn(TAG, file.getTargetFile());
        if (file.getType() == "safe-scripting-generate") {
            vScripts.push_back(file);
        }
    }

    std::vector<WSJCppPackageManagerDependence> vDeps = pkg.getListOfDependencies();
    for (int i = 0; i < vDeps.size(); i++) {
        WSJCppPackageManagerDependence dep = vDeps[i];
        std::string sInstallationDir = dep.getInstallationDir();
        // WSJCppLog::warn(TAG, sInstallationDir);
        WSJCppPackageManager pkgHold(sInstallationDir, pkg.getDir(), true);
        if (!pkgHold.load()) {
            WSJCppLog::err(TAG, "Could not load package from '" + sInstallationDir + "'");
            return -1;
        }
        std::vector<WSJCppPackageManagerDistributionFile> vFilesDep = pkgHold.getListOfDistributionFiles();
        for (int n = 0; n < vFilesDep.size(); n++) {
            WSJCppPackageManagerDistributionFile file = vFilesDep[n];
            // WSJCppLog::warn(TAG, file.getTargetFile());
            if (file.getType() == "safe-scripting-generate") {
                vScripts.push_back(file);
            }
        }        
    }

    std::string sOutput = "";

    if (vScripts.size() == 0) {
        sOutput = "\n Generate not found ";
    } else {
        sOutput = "\n\n Generate: \n";
    }
    
    for (int i = 0; i < vScripts.size(); i++) {
        std::string sFileName = vScripts[i].getTargetFile();
        std::vector<std::string> vSplit = WSJCppCore::split(sFileName, ".");
        if (vSplit.size() != 2) {
            sOutput += " - ERROR: Wrong script name: '" + sFileName + "' must like 'generate.ScriptName'\n";
        } else {
            if (vSplit[0] != "generate") {
                sOutput += " - ERROR: Wrong script name: '" + sFileName + "' (left part must be 'generate.*')\n";
            } else {
                sOutput += " - " + vSplit[1] + "\n";
            }
        }
    }
    WSJCppLog::info(TAG, sOutput);
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorGenerateCreate::ArgumentProcessorGenerateCreate() 
: WSJCppArgumentProcessor("create", "Create new template") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorGenerateCreate::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorGenerateDelete::ArgumentProcessorGenerateDelete() 
: WSJCppArgumentProcessor("delete", "Delete template") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorGenerateDelete::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------