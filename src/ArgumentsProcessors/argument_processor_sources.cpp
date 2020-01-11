#include "argument_processor_sources.h"
#include "wsjcpp_package_manager.h"

ArgumentProcessorSources::ArgumentProcessorSources() 
  : WSJCppArgumentProcessor("sources", "Templates which distribute with current source package") {
      registryProcessor(new ArgumentProcessorSourcesList());
      registryProcessor(new ArgumentProcessorSourcesAdd());
      registryProcessor(new ArgumentProcessorSourcesRemove());
}

// ---------------------------------------------------------------------

ArgumentProcessorSourcesList::ArgumentProcessorSourcesList() 
  : WSJCppArgumentProcessor("list", "List of defined sources") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorSourcesList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorSourcesAdd::ArgumentProcessorSourcesAdd() 
  : WSJCppArgumentProcessor("create", "Create new template") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorSourcesAdd::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    // "source" "target"
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorSourcesRemove::ArgumentProcessorSourcesRemove() 
  : WSJCppArgumentProcessor("remove", "Remove source file") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorSourcesRemove::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------