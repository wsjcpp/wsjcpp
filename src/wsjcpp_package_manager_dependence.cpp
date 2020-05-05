#include "wsjcpp_package_manager_dependence.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WsjcppPackageManagerDependence - main class

WsjcppPackageManagerDependence::WsjcppPackageManagerDependence() {
    TAG = "WsjcppPackageManagerDependence";
    m_pYamlDependece = nullptr;
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppPackageManagerDependence::toYAML() {
    m_pYamlDependece->getElement("url")->setValue(m_sUrl, true);
    m_pYamlDependece->getElement("name")->setValue(m_sName, true);
    m_pYamlDependece->getElement("version")->setValue(m_sVersion, true);
    m_pYamlDependece->getElement("origin")->setValue(m_sOrigin, true);
    m_pYamlDependece->getElement("installation-dir")->setValue(m_sInstallationDir, true);
    return m_pYamlDependece;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerDependence::fromYAML(WsjcppYamlItem *pYaml) {
    m_pYamlDependece = pYaml;
    if (!m_pYamlDependece->hasElement("name")) {
        WsjcppLog::err(TAG, "Missing required field 'name' in " + m_pYamlDependece->getForLogFormat());
        return false;
    } else {
        m_sName = m_pYamlDependece->getElement("name")->getValue();
    }

    if (!m_pYamlDependece->hasElement("version")) {
        WsjcppLog::err(TAG, "Missing required field 'version' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sVersion = m_pYamlDependece->getElement("version")->getValue();
    }

    if (!m_pYamlDependece->hasElement("url")) {
        WsjcppLog::err(TAG, "Missing required field 'url' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sUrl = m_pYamlDependece->getElement("url")->getValue();
    }

    if (!m_pYamlDependece->hasElement("installation-dir")) {
        WsjcppLog::err(TAG, "Missing required field 'installation-dir' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sInstallationDir = m_pYamlDependece->getElement("installation-dir")->getValue();
    }

    return true;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerDependence::getInstallationDir() const {
    return m_sInstallationDir;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerDependence::getUrl() const {
    return m_sUrl;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerDependence::getName() const {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerDependence::getVersion() const {
    return m_sVersion;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerDependence::getOrigin() const {
    return m_sOrigin;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerDependence::setName(const std::string &sName) {
    m_sName = sName;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerDependence::setVersion(const std::string &sVersion) {
    m_sVersion = sVersion;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerDependence::setOrigin(const std::string &sOrigin) {
    m_sOrigin = sOrigin;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerDependence::setUrl(const std::string &sUrl) {
    m_sUrl = sUrl;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerDependence::setInstallationDir(const std::string &sInstallationDir) {
    m_sInstallationDir = sInstallationDir;
}