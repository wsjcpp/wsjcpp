#include "argument_processor_change.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>
#include <wsjcpp_safe_scripting.h>

// ---------------------------------------------------------------------
// ArgumentProcessorChange

ArgumentProcessorChange::ArgumentProcessorChange() 
: WsjcppArgumentProcessor({"change", "ch"}, "Change some basic variables in wsjcpp.yml", "Change some basic variables in wsjcpp.yml") {
    registryProcessor(new ArgumentProcessorChangeVersion());
    // registryProcessor(new ArgumentProcessorGenerateCreate());
    // registryProcessor(new ArgumentProcessorGenerateDelete());
}

// ---------------------------------------------------------------------

int ArgumentProcessorChange::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------
// ArgumentProcessorChangeVersion

ArgumentProcessorChangeVersion::ArgumentProcessorChangeVersion() 
: WsjcppArgumentProcessor({"version", "ver"}, "Change version of current wsjcpp-package", "Change version of current wsjcpp-package") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorChangeVersion::exec(
    const std::vector<std::string> &vRoutes, 
    const std::vector<std::string> &vSubParams
) {

    if (vSubParams.size() == 0) {
        std::cout << "Expected parameter %version%" << std::endl;
        return -1;
    }
    std::string sVersion = vSubParams[0];

    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (!pkg.setVersion(sVersion)) {
        return -1;
    }

    pkg.save();
    pkg.updateAutogeneratedFiles();
    return 0;

    /*std::vector<WsjcppPackageManagerSafeScriptingGenerate> vScripts = pkg.getListOfSafeScriptingGenerate();

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
    */
    return 0;
}