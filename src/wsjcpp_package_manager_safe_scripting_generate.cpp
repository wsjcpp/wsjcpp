#include "wsjcpp_package_manager_safe_scripting_generate.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WSJCppPackageManagerDistributionFile

WSJCppPackageManagerSafeScriptingGenerate::WSJCppPackageManagerSafeScriptingGenerate() {
    TAG = "WSJCppPackageManagerSafeScriptingGenerate";
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerSafeScriptingGenerate::getName() const {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerSafeScriptingGenerate::getFullPath() const {
    return m_sFullPath;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerSafeScriptingGenerate::getModuleName() const {
    return m_sModuleName;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerSafeScriptingGenerate::setName(const std::string &sName) {
    m_sName = sName;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerSafeScriptingGenerate::setFullPath(const std::string &sFullPath) {
    m_sFullPath = sFullPath;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerSafeScriptingGenerate::setModuleName(const std::string &sModuleName) {
    m_sModuleName = sModuleName;
}