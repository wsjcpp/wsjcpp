#include "argument_processor_generate.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>
#include <wsjcpp_safe_scripting.h>

// ---------------------------------------------------------------------
// ArgumentProcessorGenerate

ArgumentProcessorGenerate::ArgumentProcessorGenerate() 
: WSJCppArgumentProcessor("generate", "Generate source code snippets/templates/examples") {
    registryProcessor(new ArgumentProcessorGenerateList());

    // registryProcessor(new ArgumentProcessorGenerateCreate());
    // registryProcessor(new ArgumentProcessorGenerateDelete());
}

// ---------------------------------------------------------------------

int ArgumentProcessorGenerate::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() == 0) {
        WSJCppLog::err(TAG, "Expected name of components and arguments for script");
        return -1;
    }
    std::string sComponentName = vSubParams[0];

    bool bFound = false;
    WSJCppPackageManagerSafeScriptingGenerate gen;
    std::vector<WSJCppPackageManagerSafeScriptingGenerate> vScripts = pkg.getListOfSafeScriptingGenerate();
    for (int i = 0; i < vScripts.size(); i++) {
        if (vScripts[i].getName() == sComponentName) {
            gen = vScripts[i];
            bFound = true;
        }
    }

    if (!bFound) {
        WSJCppLog::err(TAG, "Not found component with name '" + sComponentName + "'");
        return -1;
    }

    if (!WSJCppCore::fileExists(gen.getFullPath())) {
        WSJCppLog::err(TAG, "File not found '" + gen.getFullPath() + "'");
        return -1;
    }

    std::string sScriptContent;
    WSJCppCore::readTextFile(gen.getFullPath(), sScriptContent);

    WSJCppSafeScriptingContext scriptContext;
    std::vector<std::string> vScriptArgs;
    for (int i = 0; i < vSubParams.size(); i++) {
        if (i != 0) {
            vScriptArgs.push_back(vSubParams[i]);
        }
    }

    int nResult = scriptContext.exec(
        WSJCppCore::getCurrentDirectory(), 
        gen.getFullPath(), 
        sScriptContent,
        vScriptArgs
    );

    return nResult;
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
        sOutput = "\n Components not found ";
    } else {
        sOutput = "\n\n Components: \n";
    }

    for (int i = 0; i < vScripts.size(); i++) {
        sOutput += " - " + vScripts[i].getName() + "\n";
        if (m_bMore) {
            sOutput += 
                "     from package: '" + vScripts[i].getModuleName() + "' \n"
                "     script path: '" + vScripts[i].getFullPath() + "'\n";
        }
    }
    WSJCppLog::info(TAG, sOutput);
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorGenerateCreate

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