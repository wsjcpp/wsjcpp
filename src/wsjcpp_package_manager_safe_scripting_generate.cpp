#include "wsjcpp_package_manager_safe_scripting_generate.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WsjcppPackageManagerDistributionFile

WsjcppPackageManagerSafeScriptingGenerate::WsjcppPackageManagerSafeScriptingGenerate() {
    TAG = "WsjcppPackageManagerSafeScriptingGenerate";
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerSafeScriptingGenerate::getName() const {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerSafeScriptingGenerate::getFullPath() const {
    return m_sFullPath;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerSafeScriptingGenerate::getModuleName() const {
    return m_sModuleName;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerSafeScriptingGenerate::setName(const std::string &sName) {
    m_sName = sName;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerSafeScriptingGenerate::setFullPath(const std::string &sFullPath) {
    m_sFullPath = sFullPath;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerSafeScriptingGenerate::setModuleName(const std::string &sModuleName) {
    m_sModuleName = sModuleName;
}