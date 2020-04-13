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
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerResourceFile::fromYAML(WsjcppYamlItem *pYamlDistributionFile, bool bHolded) {
    m_bHolded = bHolded;
    m_pYamlResourceFile = pYamlDistributionFile;

    if (!m_pYamlResourceFile->hasElement("filepath")) {
        WsjcppLog::err(TAG, "Missing required field 'filepath' in " + m_pYamlResourceFile->getForLogFormat());
        return false; 
    }

    std::vector<std::string> vKeys = m_pYamlResourceFile->getKeys();
    for (int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        if (sKey == "filepath") {
            m_sFilepath = m_pYamlResourceFile->getElement("filepath")->getValue();
            if (!WsjcppCore::fileExists(m_sFilepath)) {
                WsjcppLog::warn(TAG, "File resource '" + m_sFilepath + "' did not exists in " + m_pYamlResourceFile->getForLogFormat());
            }
        }
    }

    if (!m_pYamlResourceFile->hasElement("filesize")) {
        WsjcppLog::err(TAG, "Missing required field 'filesize' in " + m_pYamlResourceFile->getForLogFormat());
        return false; 
    } else {
        std::string sFileSize = m_pYamlResourceFile->getElement("filesize")->getValue();
        m_nFilesize = std::atoi(sFileSize.c_str());
    }
    
    if (!m_pYamlResourceFile->hasElement("sha1")) {
        m_pYamlResourceFile->setElementValue("sha1", false, "", true);
        WsjcppLog::err(TAG, "Missing required field 'sha1' in " + m_pYamlResourceFile->getForLogFormat());
        return false; 
    } else {
        m_sSha1 = m_pYamlResourceFile->getElement("sha1")->getValue();
    }

    if (!m_pYamlResourceFile->hasElement("pack-as")) {
        WsjcppLog::err(TAG, "Missing required field 'pack-as' in " + m_pYamlResourceFile->getForLogFormat());
        return false;
    } else {
        m_sPackAs = m_pYamlResourceFile->getElement("pack-as")->getValue();
        if (m_sPackAs != "text" && m_sPackAs != "binary") {
            WsjcppLog::err(TAG, "Field 'pack-as' must contains 'text' or 'binary' in " + m_pYamlResourceFile->getForLogFormat());
            return false;
        }
    }

    if (!m_pYamlResourceFile->hasElement("modified")) {
        WsjcppLog::err(TAG, "Missing required field 'modified' in " + m_pYamlResourceFile->getForLogFormat());
        return false; 
    } else {
        std::string sModified = m_pYamlResourceFile->getElement("modified")->getValue();
        m_nModified = std::atoi(sModified.c_str());
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

std::string WsjcppPackageManagerResourceFile::getFilepath() {
    return m_sFilepath;
}

// ---------------------------------------------------------------------

long WsjcppPackageManagerResourceFile::getFilesize() {
    return m_nFilesize;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerResourceFile::getSha1() {
    return m_sSha1;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerResourceFile::getPackAs() {
    return m_sPackAs;
}

// ---------------------------------------------------------------------

long WsjcppPackageManagerResourceFile::getModified() {
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
