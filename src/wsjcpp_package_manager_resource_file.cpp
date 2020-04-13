#include "wsjcpp_package_manager_resource_file.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WsjcppPackageManagerResourceFile

WsjcppPackageManagerResourceFile::WsjcppPackageManagerResourceFile() {
    TAG = "WsjcppPackageManagerResourceFile";
    m_sFilepath = "";
    m_nFilesize = 0;
    m_sSha1 = "sha1";
    m_sPackAs = "binary";
    m_nModified = 0;
    m_bHolded = false;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerResourceFile::fromYAML(WsjcppYamlItem *pYamlDistributionFile, bool bHolded) {
    m_pYamlResourceFile = pYamlDistributionFile;
    m_bHolded = bHolded;
    if (!m_pYamlResourceFile->hasElement("filepath")) {
        WsjcppLog::err(TAG, "Missing required field 'filepath' in " + m_pYamlResourceFile->getForLogFormat());
        return false; 
    }

    if (!m_pYamlResourceFile->hasElement("filesize")) {
        WsjcppLog::err(TAG, "Missing required field 'filesize' in " + m_pYamlResourceFile->getForLogFormat());
        return false; 
    }

    if (!m_pYamlResourceFile->hasElement("sha1")) {
        WsjcppLog::err(TAG, "Missing required field 'sha1' in " + m_pYamlResourceFile->getForLogFormat());
        return false; 
    }

    if (!m_pYamlResourceFile->hasElement("pack-as")) {
        WsjcppLog::err(TAG, "Missing required field 'pack-as' in " + m_pYamlResourceFile->getForLogFormat());
        return false;
    }

    if (!m_pYamlResourceFile->hasElement("modified")) {
        WsjcppLog::err(TAG, "Missing required field 'modified' in " + m_pYamlResourceFile->getForLogFormat());
        return false; 
    }

    std::vector<std::string> vKeys = m_pYamlResourceFile->getKeys();
    for (int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        if (sKey == "filepath") {
            m_sFilepath = m_pYamlResourceFile->getElement("filepath")->getValue();
            if (!m_bHolded && !WsjcppCore::fileExists(m_sFilepath)) {
                WsjcppLog::warn(TAG, "File resource '" + m_sFilepath + "' did not exists in " + m_pYamlResourceFile->getForLogFormat());
            }
        } else if (sKey == "filesize") {
            std::string sFileSize = m_pYamlResourceFile->getElement("filesize")->getValue();
            m_nFilesize = std::atoi(sFileSize.c_str());
        } else if (sKey == "sha1") {
            m_sSha1 = m_pYamlResourceFile->getElement("sha1")->getValue();
        } else if (sKey == "pack-as") {
            m_sPackAs = m_pYamlResourceFile->getElement("pack-as")->getValue();
            if (m_sPackAs != "text" && m_sPackAs != "binary") {
                WsjcppLog::err(TAG, "Field 'pack-as' must contains 'text' or 'binary' in " + m_pYamlResourceFile->getForLogFormat());
                return false;
            }
        } else if (sKey == "modified") {
            std::string sModified = m_pYamlResourceFile->getElement("modified")->getValue();
            m_nModified = std::atoi(sModified.c_str());
        } else {
            WsjcppLog::warn(TAG, "Excess field '" + sKey + "' in " + m_pYamlResourceFile->getElement(sKey)->getForLogFormat());
        }
    }
    return true;
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppPackageManagerResourceFile::toYAML() {
    m_pYamlResourceFile->getElement("filepath")->setValue(m_sFilepath, true);
    m_pYamlResourceFile->getElement("filesize")->setValue(std::to_string(m_nFilesize), false);
    m_pYamlResourceFile->getElement("sha1")->setValue(m_sSha1, true);
    m_pYamlResourceFile->getElement("pack-as")->setValue(m_sPackAs, true);
    m_pYamlResourceFile->getElement("modified")->setValue(std::to_string(m_nModified), false);
    return m_pYamlResourceFile;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerResourceFile::getFilepath() const {
    return m_sFilepath;
}

// ---------------------------------------------------------------------

long WsjcppPackageManagerResourceFile::getFilesize() const {
    return m_nFilesize;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerResourceFile::getSha1() const {
    return m_sSha1;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerResourceFile::getPackAs() const {
    return m_sPackAs;
}

// ---------------------------------------------------------------------

long WsjcppPackageManagerResourceFile::getModified() const {
    return m_nModified;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerResourceFile::setFilepath(const std::string &sFilepath) {
    m_sFilepath = sFilepath;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerResourceFile::setFilesize(long nFilesize) {
    m_nFilesize = nFilesize;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerResourceFile::setSha1(const std::string &sSha1) {
    m_sSha1 = sSha1;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerResourceFile::setPackAs(const std::string &sPackAs) {
    m_sPackAs = sPackAs;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerResourceFile::setModified(long nModified) {
    m_nModified = nModified;
}

// ---------------------------------------------------------------------
