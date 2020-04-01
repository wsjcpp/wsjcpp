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
    registrySingleArgument("--more", "More details");
    m_bMore = false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorGenerateList::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--more") {
        m_bMore = true;
        return true;
    }
    return false;
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

    std::vector<WSJCppPackageManagerSafeScriptingGenerate> vScripts = pkg.getListOfSafeScriptingGenerate();

    std::string sOutput = "";

    if (vScripts.size() == 0) {
        sOutput = "\n Generate not found ";
    } else {
        sOutput = "\n\n Generate: \n";
    }

    for (int i = 0; i < vScripts.size(); i++) {
        sOutput += " - " + vScripts[i].getName() + "\n";
        if (m_bMore) {
            sOutput += 
                "     from module: '" + vScripts[i].getModuleName() + "' \n"
                "     script path: '" + vScripts[i].getFullPath() + "'\n";
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