#include "argument_processor_generate.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>
#include <wsjcpp_safe_scripting.h>

// ---------------------------------------------------------------------
// ArgumentProcessorGenerate

ArgumentProcessorGenerate::ArgumentProcessorGenerate() 
: WsjcppArgumentProcessor({"generate", "gen"}, "Generate source code snippets/templates/examples", "Generate source code snippets/templates/examples") {
    registryProcessor(new ArgumentProcessorGenerateList());
    // registryProcessor(new ArgumentProcessorGenerateCreate());
    // registryProcessor(new ArgumentProcessorGenerateDelete());
}

// ---------------------------------------------------------------------

int ArgumentProcessorGenerate::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() == 0) {
        WsjcppLog::err(TAG, "Expected name of components and arguments for script");
        return -1;
    }
    std::string sComponentName = vSubParams[0];

    bool bFound = false;
    WsjcppPackageManagerSafeScriptingGenerate gen;
    std::vector<WsjcppPackageManagerSafeScriptingGenerate> vScripts = pkg.getListOfSafeScriptingGenerate();
    for (int i = 0; i < vScripts.size(); i++) {
        if (vScripts[i].getName() == sComponentName) {
            gen = vScripts[i];
            bFound = true;
        }
    }

    if (!bFound) {
        WsjcppLog::err(TAG, "Not found component with name '" + sComponentName + "'");
        return -1;
    }

    if (!WsjcppCore::fileExists(gen.getFullPath())) {
        WsjcppLog::err(TAG, "File not found '" + gen.getFullPath() + "'");
        return -1;
    }

    std::string sScriptContent;
    WsjcppCore::readTextFile(gen.getFullPath(), sScriptContent);

    WsjcppSafeScriptingContext scriptContext;
    std::vector<std::string> vScriptArgs;
    for (int i = 0; i < vSubParams.size(); i++) {
        if (i != 0) {
            vScriptArgs.push_back(vSubParams[i]);
        }
    }

    int nResult = scriptContext.exec(
        WsjcppCore::getCurrentDirectory(), 
        gen.getFullPath(), 
        sScriptContent,
        vScriptArgs
    );

    return nResult;
}

// ---------------------------------------------------------------------

ArgumentProcessorGenerateList::ArgumentProcessorGenerateList() 
: WsjcppArgumentProcessor({"list", "ls"}, "List of defined templates", "List of defined templates") {
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
    const std::vector<std::string> &vRoutes, 
    const std::vector<std::string> &vSubParams
) {

    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    std::vector<WsjcppPackageManagerSafeScriptingGenerate> vScripts = pkg.getListOfSafeScriptingGenerate();

    std::string sOutput = "";

    if (vScripts.size() == 0) {
        sOutput = "\n Generates not found ";
    } else {
        sOutput = "\n Generates: \n";
    }

    for (int i = 0; i < vScripts.size(); i++) {
        sOutput += " - wsjcpp generate " + vScripts[i].getName() + " YourClassName\n";
        if (m_bMore) {
            sOutput += 
                "     from package: '" + vScripts[i].getModuleName() + "' \n"
                "     script path: '" + vScripts[i].getFullPath() + "'\n";
        }
    }
    std::cout << sOutput << std::endl;
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorGenerateCreate

ArgumentProcessorGenerateCreate::ArgumentProcessorGenerateCreate() 
: WsjcppArgumentProcessor({"create"}, "Create new template", "Create new template") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorGenerateCreate::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorGenerateDelete::ArgumentProcessorGenerateDelete() 
: WsjcppArgumentProcessor({"delete"}, "Delete template", "Delete template") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorGenerateDelete::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------