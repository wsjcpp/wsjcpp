/*
 * MIT License
 *
 * Copyright (c) 2019-2026 Evgenii Sopov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

// original source-code: https://github.com/wsjcpp/wsjcpp

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

WsjcppYamlNode *WsjcppPackageManagerAuthor::toYAML() {
    m_pYamlAuthor->getElement("name")->setValue(m_sName, WSJCPP_YAML_QUOTES_NONE);
    m_pYamlAuthor->getElement("email")->setValue(m_sEmail, WSJCPP_YAML_QUOTES_NONE);
    m_pYamlAuthor->getElement("web-site")->setValue(m_sWebSite, WSJCPP_YAML_QUOTES_NONE);
    return m_pYamlAuthor;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerAuthor::fromYAML(WsjcppYamlNode *pYamlAuthor) {
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