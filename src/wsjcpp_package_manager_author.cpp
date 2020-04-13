
#include "wsjcpp_package_manager_author.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WsjcppPackageManagerAuthor

WsjcppPackageManagerAuthor::WsjcppPackageManagerAuthor() {
    TAG = "WsjcppPackageManagerAuthor";
    m_sName = "";
    m_sEmail = "";
    m_pYamlAuthor = nullptr;
}

// ---------------------------------------------------------------------

WsjcppPackageManagerAuthor::WsjcppPackageManagerAuthor(const std::string &sName, const std::string &sEmail) {
    TAG = "WsjcppPackageManagerAuthor";
    m_sName = sName;
    m_sEmail = sEmail;
    m_pYamlAuthor = nullptr;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerAuthor::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerAuthor::getEmail() {
    return m_sEmail;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerAuthor::getWebSite() {
    return m_sWebSite;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerAuthor::getFullAuthor() {
    return m_sName + " <" + m_sEmail + ">";
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppPackageManagerAuthor::toYAML() {
    m_pYamlAuthor->getElement("name")->setValue(m_sName, true);
    m_pYamlAuthor->getElement("email")->setValue(m_sEmail, true);
    m_pYamlAuthor->getElement("web-site")->setValue(m_sWebSite, true);
    return m_pYamlAuthor;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerAuthor::fromYAML(WsjcppYamlItem *pYamlAuthor) {
    m_pYamlAuthor = pYamlAuthor;

    if (!m_pYamlAuthor->hasElement("name")) {
        WsjcppLog::err(TAG, "Missing required field 'name' in " + pYamlAuthor->getForLogFormat());
        return false; 
    }

    if (!m_pYamlAuthor->hasElement("email")) {
        WsjcppLog::err(TAG, "Missing required field 'email' in " + pYamlAuthor->getForLogFormat());
        return false; 
    }
    
    std::vector<std::string> vKeys = m_pYamlAuthor->getKeys();
    for (int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        if (sKey == "name") {
            m_sName = m_pYamlAuthor->getElement("name")->getValue();
        } else if (sKey == "email") {
            m_sEmail = m_pYamlAuthor->getElement("email")->getValue();
        } else if (sKey == "web-site") {
            m_sWebSite = m_pYamlAuthor->getElement("web-site")->getValue();
        } else {
            WsjcppLog::warn(TAG, "Excess field '" + sKey + "' in " + pYamlAuthor->getElement(sKey)->getForLogFormat());
        }
    }
    return true;
}