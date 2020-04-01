#include "wsjcpp_package_manager_distribution_file.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WSJCppPackageManagerDistributionFile

WSJCppPackageManagerDistributionFile::WSJCppPackageManagerDistributionFile() {
    TAG = "WSJCppPackageManagerDistributionFile";
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerDistributionFile::fromYAML(WSJCppYAMLItem *pYamlDistributionFile, bool bHolded) {
    m_bHolded = bHolded;
    m_pYamlDistributionFile = pYamlDistributionFile;
    if (!m_pYamlDistributionFile->hasElement("source-file")) {
        WSJCppLog::err(TAG, "Missing required field 'source-file' in " + m_pYamlDistributionFile->getForLogFormat());
        return false; 
    } else {
        m_sSourceFile = m_pYamlDistributionFile->getElement("source-file")->getValue();
    }

    if (!m_pYamlDistributionFile->hasElement("target-file")) {
        WSJCppLog::err(TAG, "Missing required field 'target-file' in " + m_pYamlDistributionFile->getForLogFormat());
        return false; 
    } else {
        m_sTargetFile = m_pYamlDistributionFile->getElement("target-file")->getValue();
    }

    if (m_bHolded) {
        if (!m_pYamlDistributionFile->hasElement("sha1")) {
            m_pYamlDistributionFile->setElementValue("sha1", false, "", true);
            // WSJCppLog::err(TAG, "Missing required field 'sha1' in " + m_pYamlDistributionFile->getForLogFormat());
            // return false; 
        } else {
            m_sSha1 = m_pYamlDistributionFile->getElement("sha1")->getValue();
        }

        // TODO calculate sha1 and check
        
    } else {
        if (m_pYamlDistributionFile->hasElement("sha1")) {
            WSJCppLog::warn(TAG, "Exccess field 'sha1' in " + m_pYamlDistributionFile->getForLogFormat());
        }
    }

    

    if (!m_pYamlDistributionFile->hasElement("type")) {
        WSJCppLog::err(TAG, "Missing required field 'type' in " + m_pYamlDistributionFile->getForLogFormat());
        return false; 
    } else {
        m_sType = m_pYamlDistributionFile->getElement("type")->getValue();
    }

    // TODO check possible formats

    return true;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerDistributionFile::toYAML() {
    m_pYamlDistributionFile->getElement("source-file")->setValue(m_sSourceFile, true);
    m_pYamlDistributionFile->getElement("target-file")->setValue(m_sTargetFile, true);
    m_pYamlDistributionFile->getElement("sha1")->setValue(m_sSha1, true);
    m_pYamlDistributionFile->getElement("type")->setValue(m_sType, true);
    return m_pYamlDistributionFile;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionFile::getSourceFile() {
    return m_sSourceFile;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionFile::getTargetFile() {
    return m_sTargetFile;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionFile::getSha1() {
    return m_sSha1;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionFile::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDistributionFile::setSourceFile(const std::string &sSourceFile) {
    m_sSourceFile = sSourceFile;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDistributionFile::setTargetFile(const std::string &sTargetFile) {
    m_sTargetFile = sTargetFile;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDistributionFile::setSha1(const std::string &sSha1) {
    m_sSha1 = sSha1;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDistributionFile::setType(const std::string &sType) {
    m_sType = sType;
}