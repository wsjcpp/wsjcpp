#include "argument_processor_generate.h"
#include "wsjcpp_package_manager.h"

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

int ArgumentProcessorGenerateList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
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