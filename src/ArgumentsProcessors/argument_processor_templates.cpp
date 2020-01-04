#include "argument_processor_templates.h"
#include "wsjcpp_package_manager.h"

ArgumentProcessorTemplates::ArgumentProcessorTemplates() 
  : WSJCppArgumentProcessor("templates", "Templates which distribute with current source package") {
      registryProcessor(new ArgumentProcessorTemplatesList());
      registryProcessor(new ArgumentProcessorTemplatesCreate());
      registryProcessor(new ArgumentProcessorTemplatesDelete());
}

// ---------------------------------------------------------------------

ArgumentProcessorTemplatesList::ArgumentProcessorTemplatesList() 
  : WSJCppArgumentProcessor("list", "List of defined templates") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorTemplatesList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorTemplatesCreate::ArgumentProcessorTemplatesCreate() 
  : WSJCppArgumentProcessor("create", "Create new template") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorTemplatesCreate::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorTemplatesDelete::ArgumentProcessorTemplatesDelete() 
  : WSJCppArgumentProcessor("delete", "Delete template") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorTemplatesDelete::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------