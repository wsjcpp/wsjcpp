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

#include "wsjcpp_package_manager_dependence.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WsjcppPackageManagerDependence - main class

WsjcppPackageManagerDependence::WsjcppPackageManagerDependence() {
    TAG = "WsjcppPackageManagerDependence";
    m_pYamlDependece = nullptr;
}

// ---------------------------------------------------------------------

WsjcppYamlNode *WsjcppPackageManagerDependence::toYAML() {
    m_pYamlDependece->getElement("url")->setValue(m_sUrl, WSJCPP_YAML_QUOTES_DOUBLE);
    m_pYamlDependece->getElement("name")->setValue(m_sName, WSJCPP_YAML_QUOTES_DOUBLE);
    m_pYamlDependece->getElement("version")->setValue(m_sVersion, WSJCPP_YAML_QUOTES_DOUBLE);
    m_pYamlDependece->getElement("origin")->setValue(m_sOrigin, WSJCPP_YAML_QUOTES_DOUBLE);
    m_pYamlDependece->getElement("installation-dir")->setValue(m_sInstallationDir, WSJCPP_YAML_QUOTES_DOUBLE);
    return m_pYamlDependece;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerDependence::fromYAML(WsjcppYamlNode *pYaml) {
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

    if (m_pYamlDependece->hasElement("installation-datetime")) {
        m_sInstallationDateTime = m_pYamlDependece->getElement("installation-datetime")->getValue();
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