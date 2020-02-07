#include "wsjcpp_package_manager.h"
#include <iostream>
#include <wsjcpp_core.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <curl/curl.h>
#include <wsjcpp_hashes.h>
#include <wsjcpp_core.h>
#include <stdio.h>
#include <ctype.h>

// ---------------------------------------------------------------------
// WSJCppPackageManagerDistributionFile

WSJCppPackageManagerDistributionFile::WSJCppPackageManagerDistributionFile() {
    TAG = "WSJCppPackageManagerDistributionFile";
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerDistributionFile::fromYAML(WSJCppYAMLItem *pYamlDistributionFile) {
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

    if (!m_pYamlDistributionFile->hasElement("sha1")) {
        WSJCppLog::err(TAG, "Missing required field 'sha1' in " + m_pYamlDistributionFile->getForLogFormat());
        return false; 
    } else {
        m_sSha1 = m_pYamlDistributionFile->getElement("sha1")->getValue();
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

// ---------------------------------------------------------------------
// WSJCppPackageManagerAuthor

WSJCppPackageManagerAuthor::WSJCppPackageManagerAuthor() {

}

// ---------------------------------------------------------------------

WSJCppPackageManagerAuthor::WSJCppPackageManagerAuthor(const std::string &sName, const std::string &sEmail) {
    TAG = "WSJCppPackageManagerAuthor";
    m_sName = sName;
    m_sEmail = sEmail;
    m_pYamlAuthor = nullptr;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerAuthor::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerAuthor::getEmail() {
    return m_sEmail;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerAuthor::getFullAuthor() {
    return m_sName + " <" + m_sEmail + ">";
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerAuthor::toYAML() {
    m_pYamlAuthor->getElement("name")->setValue(m_sName, true);
    m_pYamlAuthor->getElement("email")->setValue(m_sEmail, true);
    return m_pYamlAuthor;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerAuthor::fromYAML(WSJCppYAMLItem *pYamlAuthor) {
    m_pYamlAuthor = pYamlAuthor;
    if (!m_pYamlAuthor->hasElement("name")) {
        // TODO prepare in yaml getOriginalLineForError()
        WSJCppLog::err(TAG, "Missing required field 'name' in " + pYamlAuthor->getForLogFormat());
        return false; 
    } else {
        m_sName = m_pYamlAuthor->getElement("name")->getValue();
    }

    if (!m_pYamlAuthor->hasElement("email")) {
        WSJCppLog::err(TAG, "Missing required field 'email' in " + pYamlAuthor->getForLogFormat());
        return false; 
    } else {
        m_sEmail = m_pYamlAuthor->getElement("email")->getValue();
    }
    return true;
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerOrigin - server info class

WSJCppPackageManagerOrigin::WSJCppPackageManagerOrigin() {
    TAG = "WSJCppPackageManagerOrigin";
    m_pYamlOrigin = nullptr;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerOrigin::toYAML() {
    m_pYamlOrigin->setValue(m_sAddress, true);
    return m_pYamlOrigin;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerOrigin::fromYAML(WSJCppYAMLItem *pYaml) {
    m_pYamlOrigin = pYaml;
    if (!m_pYamlOrigin->hasElement("address")) {
        WSJCppLog::err(TAG, "Missing required field 'address' in " + m_pYamlOrigin->getForLogFormat());
        return false; 
    } else {
        m_sAddress = m_pYamlOrigin->getElement("address")->getValue();
    }

    if (!m_pYamlOrigin->hasElement("type")) {
        WSJCppLog::err(TAG, "Missing required field 'type' in " + m_pYamlOrigin->getForLogFormat());
        return false; 
    } else {
        m_sType = m_pYamlOrigin->getElement("type")->getValue();
    }

    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerOrigin::getAddress() {
    return m_sAddress;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerOrigin::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerOrigin::setAddress(const std::string &sAddress) {
    m_sAddress = sAddress;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerOrigin::setType(const std::string &sType) {
    m_sType = sType;
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerRepository - repository struct

WSJCppPackageManagerRepository::WSJCppPackageManagerRepository() {
    TAG = "WSJCppPackageManagerRepository";
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerRepository::toYAML() {
    m_pYamlRepository->getElement("url")->setValue(m_sUrl, true);
    m_pYamlRepository->getElement("type")->setValue(m_sType, true);
    return m_pYamlRepository;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerRepository::fromYAML(WSJCppYAMLItem *pYaml) {
    m_pYamlRepository = pYaml;
    if (!m_pYamlRepository->hasElement("type")) {
        WSJCppLog::err(TAG, "Missing required field 'type' in " + m_pYamlRepository->getForLogFormat());
        return false; 
    } else {
        m_sType = m_pYamlRepository->getElement("type")->getValue();
    }

    if (!m_pYamlRepository->hasElement("url")) {
        // TODO prepare in yaml getOriginalLineForError()
        WSJCppLog::err(TAG, "Missing required field 'url' in " + m_pYamlRepository->getForLogFormat());
        return false; 
    } else {
        m_sUrl = m_pYamlRepository->getElement("url")->getValue();
    }
    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerRepository::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerRepository::getUrl() {
    return m_sUrl;
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerUnitTest - main class

WSJCppPackageManagerUnitTest::WSJCppPackageManagerUnitTest() {
    TAG = "WSJCppPackageManagerUnitTest";
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerUnitTest::toYAML() {
    m_pYamlUnitTest->getElement("url")->setValue(m_sName, true);
    m_pYamlUnitTest->getElement("type")->setValue(m_sDescription, true);
    return m_pYamlUnitTest;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerUnitTest::fromYAML(WSJCppYAMLItem *pYaml) {
    m_pYamlUnitTest = pYaml;
    if (!m_pYamlUnitTest->hasElement("name")) {
        WSJCppLog::err(TAG, "Missing required field 'name' in " + m_pYamlUnitTest->getForLogFormat());
        return false; 
    } else {
        m_sName = m_pYamlUnitTest->getElement("name")->getValue();
    }

    if (!m_pYamlUnitTest->hasElement("description")) {
        WSJCppLog::err(TAG, "Missing required field 'description' in " + m_pYamlUnitTest->getForLogFormat());
        return false; 
    } else {
        m_sDescription = m_pYamlUnitTest->getElement("description")->getValue();
    }
    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerUnitTest::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerUnitTest::getDescription() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerUnitTest::setName(const std::string &sName) {
    m_sName = sName;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerUnitTest::setDescription(const std::string &sDescription) {
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------
// WSJCppPackageManager - main class

WSJCppPackageManagerDependence::WSJCppPackageManagerDependence() {
    TAG = "WSJCppPackageManagerDependence";
    m_pYamlDependece = nullptr;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerDependence::toYAML() {
    m_pYamlDependece->getElement("url")->setValue(m_sUrl, true);
    m_pYamlDependece->getElement("name")->setValue(m_sName, true);
    m_pYamlDependece->getElement("version")->setValue(m_sVersion, true);
    m_pYamlDependece->getElement("origin")->setValue(m_sOrigin, true);
    m_pYamlDependece->getElement("installation-dir")->setValue(m_sInstallationDir, true);
    return m_pYamlDependece;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerDependence::fromYAML(WSJCppYAMLItem *pYaml) {
    m_pYamlDependece = pYaml;
    if (!m_pYamlDependece->hasElement("name")) {
        WSJCppLog::err(TAG, "Missing required field 'name' in " + m_pYamlDependece->getForLogFormat());
        return false;
    } else {
        m_sName = m_pYamlDependece->getElement("name")->getValue();
    }

    if (!m_pYamlDependece->hasElement("version")) {
        WSJCppLog::err(TAG, "Missing required field 'version' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sVersion = m_pYamlDependece->getElement("version")->getValue();
    }

    if (!m_pYamlDependece->hasElement("url")) {
        WSJCppLog::err(TAG, "Missing required field 'url' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sUrl = m_pYamlDependece->getElement("url")->getValue();
    }

    if (!m_pYamlDependece->hasElement("installation-dir")) {
        WSJCppLog::err(TAG, "Missing required field 'installation-dir' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sInstallationDir = m_pYamlDependece->getElement("installation-dir")->getValue();
    }

    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getInstallationDir() const {
    return m_sInstallationDir;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getUrl() const {
    return m_sUrl;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getName() const {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getVersion() const {
    return m_sVersion;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getOrigin() const {
    return m_sOrigin;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setName(const std::string &sName) {
    m_sName = sName;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setVersion(const std::string &sVersion) {
    m_sVersion = sVersion;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setOrigin(const std::string &sOrigin) {
    m_sOrigin = sOrigin;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setUrl(const std::string &sUrl) {
    m_sUrl = sUrl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setInstallationDir(const std::string &sInstallationDir) {
    m_sInstallationDir = sInstallationDir;
}

// ---------------------------------------------------------------------
// WSJCppPackageManager - main class

WSJCppPackageManager::WSJCppPackageManager(const std::string &sDir) {
    TAG = "WSJCppPackageManager";
    m_sDir = sDir;
    m_sDirWithSources = m_sDir + "/src.wsjcpp";
    m_sGithubPrefix = "https://github.com/";
    // TODO m_sGithubPrefix = "git@";  // try clone project to cache directory
    m_sBitbucketPrefix = "https://bitbucket.com/";
    m_sFilePrefix = "file:///"; // from file system
    m_sHttpPrefix = "http://"; // from some http://
    m_sHttpsPrefix = "https://";
    m_sYamlFilename = "wsjcpp.yml";
    m_sWSJCppCurrentVersion = "v0.0.1";
    m_sWSJCppVersion = m_sWSJCppCurrentVersion;
    m_bHolded = false;
    m_sIssues = "none";
}

// ---------------------------------------------------------------------

WSJCppPackageManager::WSJCppPackageManager(const std::string &sDir, const std::string &sParentDir, bool bHolded) 
: WSJCppPackageManager(sDir) {
    m_sDirWithSources = m_sDir + "/src.wsjcpp";
    m_sYamlFilename = "wsjcpp.hold.yml";
    m_bHolded = true;
    m_bHasDocker = false;
    m_sParentDir = sParentDir;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManager::getDir() const {
    return m_sDir;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isHolded() const {
    return m_bHolded;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::init() {

    if (!WSJCppCore::dirExists(m_sDir)) {
        std::cout << "Directory '" << m_sDir << "' did not exists... create the dir ? (y/n)" << std::endl;
        std::string sYN;
        std::cin >> sYN;
        if (sYN == "y" || sYN == "Y") {
            WSJCppCore::makeDir(m_sDir);
        }

        if (!WSJCppCore::dirExists(m_sDir)) {
            std::cout << "ERROR: Directory '" << m_sDir << "' did not exists." << std::endl;
            return false;
        }
    }

    std::cout << "Directory: " << m_sDir << std::endl; // Type a number and press enter
    std::cout << "Source Package Name: ";
    std::getline(std::cin, m_sName);
    std::cout << "Version: ";
    std::getline(std::cin, m_sVersion);
    std::cout << "Description: ";
    std::getline(std::cin, m_sDescription);
    
    std::string sAuthorName = "";
    std::cout << "Author's Name: ";
    std::getline(std::cin, sAuthorName);

    std::string sAuthorEmail = "";
    std::cout << "Author's Email: ";
    std::getline(std::cin, sAuthorEmail);

    WSJCppPackageManagerAuthor author(sAuthorName, sAuthorEmail);
    m_vAuthors.push_back(author);
    
    for (int i = 0; i < 10; i++) {
        std::string sKeyword = "";
        std::cout << "Keyword " << (i+1) << ": ";
        std::getline(std::cin, sKeyword);
        if (sKeyword == "") {
            break;
        }
        m_vKeywords.push_back(sKeyword);
    }

    std::string sDefaultServerAddress = "sea-kg.com";
    std::string sServerAddress = "sea-kg.com";
    std::cout << "Server Address (default '" << sDefaultServerAddress << "'): ";
    std::getline(std::cin, sServerAddress);
    if (sServerAddress == "") {
        sServerAddress = sDefaultServerAddress;
    }
    // WSJCppPackageManagerServer server(sServerAddress);
    // m_vServers.push_back(server);

    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::save() {
    if (m_bHolded) {
        WSJCppLog::throw_err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WSJCppCore::dirExists(m_sDirWithSources)) {
        WSJCppCore::makeDir(m_sDirWithSources);
    }

    std::string sGitkeepFile = m_sDirWithSources + "/.gitkeep";
    if (!WSJCppCore::fileExists(sGitkeepFile)) {
        WSJCppCore::writeFile(sGitkeepFile, ""); // TODO createEmptyFile
    }
    m_yamlPackageInfo.saveToFile(m_sYamlFullpath);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::load() {
    m_sYamlFullpath = m_sDir + "/" + m_sYamlFilename;

    if (!WSJCppCore::fileExists(m_sYamlFullpath)) {
        std::cout << "ERROR: '" << m_sYamlFullpath << "' did not found" << std::endl;
        return false;
    }
    
    if (!m_yamlPackageInfo.loadFromFile(m_sYamlFullpath)) {
        return false;
    }

    std::vector<std::string> vKeys = m_yamlPackageInfo.getRoot()->getKeys();
    for (int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        // WSJCppLog::info(TAG, "Process option '" + sKey + "'");
        if (sKey == "version") {
            if (!readFieldVersion()) {
                return false;
            }
        } else if (sKey == "cmake_minimum_required") {
            if (!readFieldCMakeMinimumRequired()) {
                return false;
            }
        } else if (sKey == "cmake_cxx_standard") {
            if (!readFieldCMakeCxxStandard()) {
                return false;
            }
        } else if (sKey == "name") {
            if (!readFieldName()) {
                return false;
            }
        } else if (sKey == "description") {
            if (!readFieldDescription()) {
                return false;
            }
        } else if (sKey == "wsjcpp_version") {
            if (!readFieldWsjcppVersion()) {
                return false;
            }
        } else if (sKey == "issues") {
            if (!readFieldIssues()) {
                return false;
            }
        } else if (sKey == "keywords") {
            if (!readFieldKeywords()) {
                return false;
            }
        } else if (sKey == "authors") {
            if (!readFieldAuthors()) {
                return false;
            }
        } else if (sKey == "distribution") {
            if (!readFieldDistribution()) {
                return false;
            }
        } else if (sKey == "origins") {
            if (!readFieldOrigins()) {
                return false;
            }
        } else if (sKey == "dependencies") {
            if (!readFieldDependencies()) {
                return false;
            }
        } else if (sKey == "repositories") {
            if (!readFieldRepositories()) {
                return false;
            }
        } else if (sKey == "unit-tests") {
            if (!readFieldUnitTests()) {
                return false;
            }
        } else if (sKey == "required-libraries") {
            if (!readFieldRequiredLibraries()) {
                return false;
            }
        } else if (sKey == "required-pkg-config") {
            if (!readFieldRequiredPkgConfig()) {
                return false;
            }
        } else if (sKey == "docker") {
            m_bHasDocker = true;
            WSJCppLog::warn(TAG, "TODO read docker section");
            // if (!readFieldRequiredPkgConfig()) {
            //    return false;
            // }
        } else {
            WSJCppLog::warn(TAG, "Ignored option '" + sKey + "' in " + m_yamlPackageInfo.getRoot()->getForLogFormat());
        }
    }

    // WSJCppLog::warn(TAG, "Loaded");
    // TODO required-libraries
    // TODO required-pkg-config
    // TODO replace-dependencies
    // TODO check requered fields

    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addSourceFile(const std::string &sSourceFile, const std::string &sTargetFile, const std::string &sType) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WSJCppCore::fileExists(sSourceFile)) {
        WSJCppLog::err(TAG, "'" + sSourceFile + "' file does not exists");
        return false;
    }
    std::vector<WSJCppPackageManagerDistributionFile>::iterator it;
    for (it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            WSJCppLog::err(TAG, "This package already contained file '" + sSourceFile + "'");
            return false;
        }
    }

    std::string sContent = "";
    if (!WSJCppCore::readTextFile(sSourceFile, sContent)) {
        return false;
    }
    std::string sSha1 = WSJCppHashes::sha1_calc_hex(sContent);

    WSJCppPackageManagerDistributionFile file;
    file.setSourceFile(sSourceFile);
    file.setTargetFile(sTargetFile);
    file.setType(sType);
    file.setSha1(sSha1);
    m_vDistributionFiles.push_back(file);
    
    WSJCppYAMLItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
    WSJCppYAMLPlaceInFile pl;
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(pDist, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_MAP);
    pItem->setElementValue("source-file", false, sSourceFile, true);
    pItem->setElementValue("target-file", false, sTargetFile, true);
    pItem->setElementValue("type", false, sType, true);
    pItem->setElementValue("sha1", false, sSha1, true);
    pDist->appendElement(pItem);
    updateAutogeneratedFiles();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::removeSourceFile(const std::string &sSourceFile) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }
    bool bResult = false;
    for (auto it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            m_vDistributionFiles.erase(it);
            bResult = true;
        }
    }
    if (bResult) {
        bResult = false;
        WSJCppYAMLItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
        int nLen = pDist->getLength();
        for (int i = nLen-1; i >= 0; i--) {
            WSJCppYAMLItem *pItem = pDist->getElement(i);
            if (pItem->getElement("source-file")->getValue() == sSourceFile) {
                pDist->removeElement(i);
                bResult = true;
            }
        }
    }

    if (!bResult) {
        WSJCppLog::err(TAG, "Distribution file '" + sSourceFile + "' cound not found in this package");
    } else {
        updateAutogeneratedFiles();
    }
    
    return bResult;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateSourceFile(const std::string &sSourceFile) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WSJCppCore::fileExists(sSourceFile)) {
        WSJCppLog::err(TAG, "'" + sSourceFile + "' file does not exists");
        return false;
    }

    std::string sContent = "";
    if (!WSJCppCore::readTextFile(sSourceFile, sContent)) {
        return false;
    }
    std::string sSha1 = WSJCppHashes::sha1_calc_hex(sContent);

    WSJCppLog::info(TAG, "'" + sSourceFile + "' some");

    bool bFound = false;
    std::vector<WSJCppPackageManagerDistributionFile>::iterator it;
    for (it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            it->setSha1(sSha1);
            bFound = true;
        }
    }

    if (!bFound) {
        WSJCppLog::err(TAG, "'" + sSourceFile + "' file not found in list. Please add this before");
        return false;
    }

    if (bFound) {
        bFound = false;
        WSJCppYAMLItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
        int nLen = pDist->getLength();
        for (int i = nLen-1; i >= 0; i--) {
            WSJCppYAMLItem *pItem = pDist->getElement(i);
            if (pItem->getElement("source-file")->getValue() == sSourceFile) {
                pItem->getElement("sha1")->setValue(sSha1, true);
                bFound = true;
            }
        }
    }
    updateAutogeneratedFiles();
    return bFound;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::createUnitTest(const std::string &sUnitTestName, const std::string &sUnitTestDescription) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }
    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    if (sName != sUnitTestName) {
        WSJCppLog::warn(TAG, "UnitTest name was normalized '" + sUnitTestName + "' -> '" + sName + "'");
    }

    for (int i = 0; i < m_vUnitTests.size(); i++) {
        if (m_vUnitTests[i].getName() == sName) {
            WSJCppLog::err(TAG, "Unit test with name '" + sName + "' already exists");
            return false;
        }
    }

    WSJCppPackageManagerUnitTest unitTest;
    unitTest.setName(sName);
    unitTest.setDescription(sUnitTestDescription);
    m_vUnitTests.push_back(unitTest);
    
    m_yamlPackageInfo.getRoot()->createElementMap("unit-tests", false);
    WSJCppYAMLItem *pUnitTests = m_yamlPackageInfo.getRoot()->getElement("unit-tests");
    pUnitTests->createElementArray("cases", false);
    WSJCppYAMLItem *pCases = pUnitTests->getElement("cases");

    WSJCppYAMLItem *pNewItem = pCases->createElementMap();
    pNewItem->setElementValue("name", false, sName, true);
    pNewItem->setElementValue("description", false, sUnitTestDescription, true);

    if (!updateAutogenerateFileUnitTestHeader(sName)) {
        return false;
    }

    if (!updateAutogenerateFileUnitTestSource(sName)) {
        return false;
    }

    updateAutogeneratedFiles();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::deleteUnitTest(const std::string &sUnitTestName) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "Package is holded");
        return false;
    }

    bool bFound = false;
    std::vector<WSJCppPackageManagerUnitTest>::iterator it; 
    for (it = m_vUnitTests.begin(); it < m_vUnitTests.end(); ++it) {
        if (it->getName() == sUnitTestName) {
            bFound = true;
            m_vUnitTests.erase(it);
            break;
        }
    }
    if (!bFound) {
        return false;    
    }
    WSJCppYAMLItem *pItem = m_yamlPackageInfo["unit-tests"].getElement("cases");
    int nLength = pItem->getLength();
    for (int i = 0; i < nLength; i++) {
        if (pItem->getElement(i)->getElement("name")->getValue() == sUnitTestName) {
            std::string sBaseName = this->generateFilenameForUnitTest(sUnitTestName);
            std::string sFileHeader = "./unit-tests.wsjcpp/src/" + sBaseName + ".h";
            std::string sFileSource = "./unit-tests.wsjcpp/src/" + sBaseName + ".cpp";
            if (WSJCppCore::fileExists(sFileHeader)) {
                WSJCppCore::removeFile(sFileHeader);
            }
            if (WSJCppCore::fileExists(sFileSource)) {
                WSJCppCore::removeFile(sFileSource);
            }
            /*if (nLength == 1) {
                return m_yamlPackageInfo.getRoot()->removeElement("unit-tests");
            }*/
            if (pItem->removeElement(i)) {
                updateAutogeneratedFiles();
                return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addOrigin(const std::string &sAddress) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "Package is holded");
        return false;
    }
    // TODO check address format
    // TODO request online for type
    for (auto it = m_vOrigins.begin(); it != m_vOrigins.end(); ++it) {
        if (it->getAddress() == sAddress) {
            WSJCppLog::err(TAG, "Error: Origin '" + sAddress + "' already defined.");
            return false;
        }
    }

    WSJCppPackageManagerOrigin origin;
    origin.setAddress(sAddress);
    origin.setType("package-registry");
    m_vOrigins.push_back(origin);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::deleteOrigin(const std::string &sAddress) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    std::vector<WSJCppPackageManagerOrigin>::iterator it;
    for (it = m_vOrigins.begin(); it != m_vOrigins.end(); ++it) {
        if (it->getAddress() == sAddress) {
            m_vOrigins.erase(it);
            return true;
        }
    }
    WSJCppLog::err(TAG, "Origin '" + sAddress + "' did not found." );
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateDependencies() {
    if (m_bHolded) {
        std::cout << "ERROR: wsjcpp is holded" << std::endl;
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::verify() {
    std::vector<std::string> m_vVerified;

    // HERE verify current package
    
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        if (m_bHolded) {
            WSJCppPackageManager m(m_sParentDir + "/" + it->getName(), m_sParentDir, true);
            if (m.load()) {
                m.verify();
            }
        } else {
            WSJCppPackageManager m(m_sDirWithSources + "/" + it->getName(), m_sDirWithSources, true);
            if (m.load()) {
                m.verify();
            }
        }
        
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::install(const std::string &sPackage) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "Could not install package when holded");
        return false;
    }

    if (isGitHubPackage(sPackage)) {
        if (isInstalled(sPackage)) {
            WSJCppLog::err(TAG, "Package '" + sPackage + "' already installed");
            return false;
        }
        WSJCppPackageManagerDependence dep;
        if (downloadFromGithubToCache(sPackage, dep)) {
            addDependency(dep);
            return installFromCache(sPackage, dep);
        } else {
            return false;
        }
    } else if (isBitbucketPackage(sPackage)) {
        // TODO
        WSJCppLog::err(TAG, "Could not install package from bitbucket - not implemented yet");
        return false;
    } else if (isFilePackage(sPackage)) {
        // TODO
        WSJCppLog::err(TAG, "Could not install package from file - not implemented yet");
        return false;
    } else if (isHttpPackage(sPackage) || isHttpsPackage(sPackage)) {
        // TODO try find on different servers
        WSJCppLog::err(TAG, "Could not install package from http(s) - not implemented yet");
        return false;
    }

    WSJCppLog::err(TAG, "Could not install package from unknown source");
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::reinstall(const std::string &sPackage) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "Could not reinstall package when holded");
        return false;
    }

    if (!isInstalled(sPackage)) {
        WSJCppLog::err(TAG, "Package '" + sPackage + "' not installed");
        return false;
    }

    if (isGitHubPackage(sPackage)) {
        WSJCppPackageManagerDependence dep;
        if (downloadFromGithubToCache(sPackage, dep)) {
            updateDependency(dep);
            return installFromCache(sPackage, dep);
        } else {
            return false;
        }
    } else if (isBitbucketPackage(sPackage)) {
        // TODO
        WSJCppLog::err(TAG, "Could not reinstall package from bitbucket - not implemented yet");
        return false;
    } else if (isFilePackage(sPackage)) {
        // TODO
        WSJCppLog::err(TAG, "Could not reinstall package from file - not implemented yet");
        return false;
    } else if (isHttpPackage(sPackage) || isHttpsPackage(sPackage)) {
        // TODO try find on different servers
        WSJCppLog::err(TAG, "Could not reinstall package from http(s) - not implemented yet");
        return false;
    }

    WSJCppLog::err(TAG, "Could not install package from unknown source");
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::uninstall(const std::string &sPackageUrl) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "Could not reinstall package when holded");
        return false;
    }

    bool bResult = false;
    std::vector<WSJCppPackageManagerDependence>::iterator it;
    for (it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        if (it->getUrl() == sPackageUrl) {
            WSJCppPackageManagerDependence dep = *it;
            removeDependenciesFilesSafe(dep);
            m_vDependencies.erase(it);
            bResult = true;
            break;
        }
    }
    if (!bResult) {
        WSJCppLog::err(TAG, "Package '" + sPackageUrl + "' did not installed");
        return false;
    }
    WSJCppYAMLItem *pDeps = m_yamlPackageInfo.getRoot()->getElement("dependencies");
    int nLen = pDeps->getLength();
    for (int i = nLen-1; i >= 0; i--) {
        WSJCppYAMLItem *pItemMap = pDeps->getElement(i);
        if (sPackageUrl == pItemMap->getElement("url")->getValue()) {
            pDeps->removeElement(i);
        }
    }

    // TODO remove files
    // TODO remove none defined sub-requirements

    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isGitHubPackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sGithubPrefix.size(), m_sGithubPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isBitbucketPackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sBitbucketPrefix.size(), m_sBitbucketPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isFilePackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sFilePrefix.size(), m_sFilePrefix) == 0;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isHttpPackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sHttpPrefix.size(), m_sHttpPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isHttpsPackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sHttpsPrefix.size(), m_sHttpsPrefix) == 0;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::addDependency(WSJCppPackageManagerDependence &dep) {
    m_vDependencies.push_back(dep);
    WSJCppYAMLItem *pDeps = m_yamlPackageInfo.getRoot()->getElement("dependencies");
    WSJCppYAMLPlaceInFile pl;
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(pDeps, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_MAP);
    // TODO add simplyfy method
    WSJCppYAMLItem *pItemName = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemName->setName("name", false);
    pItemName->setValue(dep.getName(), true);
    pItem->setElement("name", pItemName);
    WSJCppYAMLItem *pItemVersion = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemVersion->setName("version", false);
    pItemVersion->setValue(dep.getVersion(), true);
    pItem->setElement("version", pItemVersion);
    WSJCppYAMLItem *pItemURL = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemURL->setName("url", false);
    pItemURL->setValue(dep.getUrl(), true);
    pItem->setElement("url", pItemURL);
    WSJCppYAMLItem *pItemOrigin = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemOrigin->setName("origin", false);
    pItemOrigin->setValue(dep.getOrigin(), true);
    pItem->setElement("origin", pItemOrigin);
    WSJCppYAMLItem *pItemInstallationDir = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemInstallationDir->setName("installation-dir", false);
    pItemInstallationDir->setValue(dep.getInstallationDir(), true);
    pItem->setElement("installation-dir", pItemInstallationDir);
    pDeps->appendElement(pItem);
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::updateDependency(WSJCppPackageManagerDependence &dep) {
    WSJCppYAMLItem *pDeps = m_yamlPackageInfo.getRoot()->getElement("dependencies");
    int nLen = pDeps->getLength();
    for (int i = 0; i < nLen; i++) {
        WSJCppYAMLItem *pItem = pDeps->getElement(i);
        std::string sUrl = pItem->getElement("url")->getValue();
        if (dep.getUrl() == sUrl) {
            pItem->getElement("version")->setValue(dep.getVersion(), true);
            pItem->getElement("name")->setValue(dep.getName(), true);
            // pItem->getElement("url")->setValue(dep.getUrl(), true);
            pItem->getElement("origin")->setValue(dep.getOrigin(), true);
            pItem->getElement("installation-dir")->setValue(dep.getInstallationDir(), true);
        }
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::downloadFromGithubToCache(const std::string &sPackage, WSJCppPackageManagerDependence &dep) {

    std::cout << "Download package from https://github.com/ ..." << std::endl;

    std::string sPackageGithubPath = sPackage.substr(m_sGithubPrefix.size());
    // std::cout << "sPackageGithubPath: " << sPackageGithubPath << std::endl;
    std::istringstream f(sPackageGithubPath);
    std::string packageName = "";
    std::string s;
    if (getline(f, s, ':')) {
        packageName = s;
    }
    std::string packageVersion = sPackageGithubPath.substr(packageName.size()+1);
    std::string sWsjcppBaseUrl = "https://raw.githubusercontent.com/" + packageName + "/" + packageVersion + "/";

    std::string sWsjcppUrl = sWsjcppBaseUrl + "/wsjcpp.yml";
    std::string sCacheDir = m_sDir + "/.wsjcpp/cache";
    if (!WSJCppCore::dirExists(sCacheDir)) {
        WSJCppCore::makeDir(sCacheDir);
    }

    std::string sCacheSubFolderName = sCacheDir + "/" + this->prepareCacheSubFolderName(sPackage);

    if (!WSJCppCore::dirExists(sCacheSubFolderName)) {
        WSJCppCore::makeDir(sCacheSubFolderName);
    }

    std::string sDownloadedWsjCppYml = sCacheSubFolderName + "/wsjcpp.hold.yml";

    if (!this->downloadFileOverHttps(sWsjcppBaseUrl + "/wsjcpp.yml", sDownloadedWsjCppYml)) {
        WSJCppLog::err(TAG, "Could not download " + sWsjcppBaseUrl);
        // TODO remove from cache
        return false;
    }

    WSJCppPackageManager pkg(sCacheSubFolderName, sCacheSubFolderName, true);
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load " + sCacheSubFolderName);
        return false;
    }

    // sources
    std::vector<WSJCppPackageManagerDistributionFile> vSources = pkg.getListOfDistributionFiles();
    for (int i = 0; i < vSources.size(); i++) {
        WSJCppPackageManagerDistributionFile src = vSources[i];
        std::string sDownloadedWsjCppSourceFrom = sWsjcppBaseUrl + "/" + src.getSourceFile();
        std::string sDownloadedWsjCppSourceTo = sCacheSubFolderName + "/" + src.getTargetFile();

        WSJCppLog::info(TAG, "\n\t" + sDownloadedWsjCppSourceFrom + " \n\t-> \n\t" + sDownloadedWsjCppSourceTo + "\n\t[sha1:" + src.getSha1() + "]");
        if (!this->downloadFileOverHttps(sDownloadedWsjCppSourceFrom, sDownloadedWsjCppSourceTo)) {
            WSJCppLog::err(TAG, "Could not download " + sDownloadedWsjCppSourceFrom);
            // TODO remove from cache
            return false;
        }
        std::string sContent = "";
        if (!WSJCppCore::readTextFile(sDownloadedWsjCppSourceTo, sContent)) {
            WSJCppLog::err(TAG, "Could not read file " + sDownloadedWsjCppSourceTo);
            return false;
        }
        // calculate sha1
        std::string sSha1 = WSJCppHashes::sha1_calc_hex(sContent);
        if (sSha1 != src.getSha1()) {
            WSJCppLog::warn(TAG, "Expected sha1 '" + sSha1 + "', but got '" + src.getSha1() + "'");
        }
    }

    std::string sInstallationDir = "./src.wsjcpp/" + this->prepareCacheSubFolderName(pkg.getName());

    // WSJCppPackageManagerDependence dep;
    dep.setName(pkg.getName());
    dep.setVersion(pkg.getVersion());
    dep.setUrl(sPackage);
    dep.setInstallationDir(sInstallationDir);
    dep.setOrigin("https://github.com/");
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isInstalled(const std::string &sPackage) {
    // todo check in current dependencies
    for (int i = 0; i < m_vDependencies.size(); i++) {
        WSJCppPackageManagerDependence dep = m_vDependencies[i];
        if (dep.getUrl() == sPackage) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::installFromCache(const std::string &sPackage, const WSJCppPackageManagerDependence &dep) {
    std::string sInstallationDir = dep.getInstallationDir();
    // TODO check path
    if (!WSJCppCore::dirExists(sInstallationDir)) {
        WSJCppCore::makeDir(sInstallationDir);
    }
    
    std::string sCacheDir = m_sDir + "/.wsjcpp/cache"; // TODO sCacheDir must be init close with init m_sDir
    std::string sCacheSubFolderName = sCacheDir + "/" + this->prepareCacheSubFolderName(sPackage);

    // TODO redesign to WSJCppCore::recoursiveCopyFiles
    // copy sources to installation dir
    // TODO copy only if sha1 equal!!!
    std::vector<std::string> vFiles = WSJCppCore::listOfFiles(sCacheSubFolderName);
    for (int i = 0; i < vFiles.size(); i++) {
        std::string sFrom = sCacheSubFolderName + "/" + vFiles[i];
        std::string sTo = sInstallationDir + "/" + vFiles[i];
	// TODO move to wsjcpp-core
        std::ifstream  src(sFrom, std::ios::binary);
        std::ofstream  dst(sTo,   std::ios::binary);
        dst << src.rdbuf();
    }
    // TODO install all dependencies
    // TODO update src.wsjcpp/
    return true;
}

// ---------------------------------------------------------------------

// TODO remove it
void WSJCppPackageManager::printInfo() {
    
    std::cout << std::endl 
        << "===== begin: wsjcpp info =====" << std::endl
        << "Name: " << m_sName << std::endl
        << "Version: " << m_sVersion << std::endl
        << "Description: " << m_sDescription
        << std::endl;
    if (m_bHolded) {
        std::cout << "Package is holded" << std::endl;
    }
    std::cout << "Directory: " << m_sDir << std::endl;
    std::cout << "wsjcpp.version = " << m_sWSJCppVersion << std::endl;
    // print keywords
    std::cout << "Keywords: " << std::endl;
    for (unsigned int i = 0; i < m_vKeywords.size(); i++) {
        std::cout << " - " << m_vKeywords[i] << std::endl;
    }
    if (m_vDistributionFiles.size() > 0) {
        std::cout << std::endl << "Distribution-Files: " << std::endl;
        for (unsigned int i = 0; i < m_vDistributionFiles.size(); i++) {
            WSJCppPackageManagerDistributionFile source = m_vDistributionFiles[i];
            std::cout << " - " << source.getSourceFile() << " -> " << source.getTargetFile() << " [sha1:" << source.getSha1() << "]" << std::endl;
        }
    }
    
    // TODO: print authors
    // TODO: print deps

    std::cout << "===== end: wsjcpp info =====" << std::endl
        << std::endl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printAuthors() {
    std::cout << "Authors (" << m_sName << ":" << m_sVersion << "): " << std::endl;
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WSJCppPackageManagerAuthor author = m_vAuthors[i];
        std::cout << " - " << author.getFullAuthor() << std::endl;
    }
    std::cout << std::endl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printAuthorsTree() {
    std::string sAuthors = "";
    for (int i = 0; i < m_vAuthors.size(); i++) {
        if (sAuthors.size() > 0) {
            sAuthors += ", ";
        }
        sAuthors += m_vAuthors[i].getFullAuthor();
    }
    std::cout << "Authors (" << m_sName << ":" << m_sVersion << "): " << sAuthors << std::endl;

    // TODO
    recursive_printAuthorsTree(m_vDependencies);
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::recursive_printAuthorsTree(std::vector<WSJCppPackageManagerDependence> &vDependencies) {
    for (int i = 0; i < vDependencies.size(); i++) {
        WSJCppPackageManagerDependence dep = vDependencies[i];
        std::string sInstalledDir = dep.getInstallationDir(); 

        if (WSJCppCore::dirExists(dep.getInstallationDir())) {
            WSJCppPackageManager subpkg(sInstalledDir, m_sDir, true);
            WSJCppLog::info(TAG, "Loading package '" + sInstalledDir + "'");
            if (subpkg.load()) {
                subpkg.printAuthorsTree();
            } else {
                WSJCppLog::err(TAG, "Could not load package.");
            }
        } else {
            WSJCppLog::err(TAG, "Not found installed dir: '" + sInstalledDir + "' for package: " + dep.getName() + ":" + dep.getVersion());
        }
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addAuthor(const std::string &sName, const std::string &sEmail) {
    bool bFoundAuthor = false;
    std::string sFullAuthor = sName + " <" + sEmail + ">";
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WSJCppPackageManagerAuthor author = m_vAuthors[i];
        if (author.getFullAuthor() == sFullAuthor) {
            bFoundAuthor = true;
        }
    }
    if (bFoundAuthor) {
        WSJCppLog::err(TAG, "Author already exists");
        return false;
    }

    WSJCppPackageManagerAuthor newAuthor(sName, sEmail);
    m_vAuthors.push_back(newAuthor);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::removeAuthor(const std::string &sFullAuthor) {
    std::vector<WSJCppPackageManagerAuthor> vNewAuthors;
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WSJCppPackageManagerAuthor author = m_vAuthors[i];
        if (author.getFullAuthor() != sFullAuthor) {
            vNewAuthors.push_back(author);
        }
    }
    if (vNewAuthors.size() != m_vAuthors.size()) {
        m_vAuthors.clear();
        for (int i = 0; i < vNewAuthors.size(); i++) {
            m_vAuthors.push_back(vNewAuthors[i]);
        }
        return true;
    }
    WSJCppLog::err(TAG, "Not found this author");
    return false;
}

// ---------------------------------------------------------------------

std::vector<WSJCppPackageManagerDistributionFile> WSJCppPackageManager::getListOfDistributionFiles() {
    return m_vDistributionFiles;
}

// ---------------------------------------------------------------------

std::vector<WSJCppPackageManagerDependence> WSJCppPackageManager::getListOfDependencies() {
    return m_vDependencies;
}

// ---------------------------------------------------------------------

std::vector<WSJCppPackageManagerUnitTest> WSJCppPackageManager::getListOfUnitTests() {
    return m_vUnitTests;
}

// ---------------------------------------------------------------------

std::vector<WSJCppPackageManagerOrigin> WSJCppPackageManager::getListOfOrigins() {
    return m_vOrigins;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManager::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManager::getVersion() {
    return m_sVersion;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManager::normalizeUnitTestName(const std::string &sUnitTestName, bool bSilent) {
    std::string sRet = ""; 
    for (int i = 0; i < sUnitTestName.size(); i++) {
        char c = sUnitTestName[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            sRet += c;
        } else {
            if (!bSilent) {
                WSJCppLog::warn(TAG, std::string("Ignored symbol in UnitTest Name") + c);
            }
        }
    }
    return sRet;
}

// ---------------------------------------------------------------------
// TODO test for this
std::string WSJCppPackageManager::generateFilenameForUnitTest(const std::string &sUnitTestName) {
    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    std::string sRet = "";
    for (int i = 0; i < sName.size(); i++) {
        char c = sUnitTestName[i];
        if (c >= 'A' && c <= 'Z') {
            c = char(c + 32);
            sRet += sRet.length() == 0 ? "" : "_";
            sRet += c;
        } else if (c >= 'a' && c <= 'z') {
            sRet += c;
        } else if (c >= '0' && c <= '9') {
            sRet += c;
        } else {
            WSJCppLog::warn(TAG, std::string("Ignored ") + c);
        }
    }
    return "unit_test_" + sRet;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogeneratedFiles() {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "Could not reinstall package when holded");
        return false;
    }

    // TODO update hashes for distribution files

    if (!updateAutogeneratedFiles_CMakeListsTXT()) {
        return false;
    }

    if (!updateAutogeneratedFiles_UnitTests()) {
        return false;
    }

    if (!updateAutogeneratedFiles_Dockerfiles()) {
        return false;
    }

    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManager::prepareCacheSubFolderName(const std::string &sPackage) {
    std::string ret = sPackage;
    std::string illegalChars = "\\/:?\"<>|.-";
    std::string::iterator it;
    for (it = ret.begin(); it < ret.end() ; ++it) {
        if (illegalChars.find(*it) != std::string::npos) {
            *it = '_';
        }
    }
    return ret;
}

// ---------------------------------------------------------------------

size_t CurlWrite_CallbackFunc_DataToFile(void *ptr, size_t size, size_t nmemb, FILE *stream) { 
    size_t written = fwrite(ptr, size, nmemb, stream); 
    return written; 
}

bool WSJCppPackageManager::downloadFileOverHttps(const std::string &sUrl, const std::string &sPath) {
    WSJCppLog::info(TAG, "sUrl: '" + sUrl + "'");
    WSJCppLog::info(TAG, "sPath: '" + sPath + "'");
    std::string sUserAgent = "wsjcpp/" + m_sWSJCppCurrentVersion;
    CURL *curl;
    FILE *fp = fopen(sPath.c_str(),"wb"); 
    if (fp == NULL) { 
        WSJCppLog::err(TAG, "Could not open file for write '" + sPath + "'"); 
        return false;
    }

    CURLcode res;
    curl = curl_easy_init(); 
    if (curl) { 
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https
        curl_easy_setopt(curl, CURLOPT_URL, sUrl.c_str()); 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_DataToFile); 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, sUserAgent.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl); 
        if (res != CURLE_OK) {
            WSJCppLog::err(TAG, "Curl failed, reason  " + std::string(curl_easy_strerror(res))); 
            // TODO remove file
            curl_easy_cleanup(curl);
            return false;
        } else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code != 200) {
                WSJCppLog::info(TAG, "end " + std::to_string(response_code));
                // TODO remove file
                curl_easy_cleanup(curl);
                return false;
            }
        }

        // always cleanup
        curl_easy_cleanup(curl); 
        fclose(fp);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldVersion() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("version")) {
        WSJCppLog::err(TAG, "Missing required field 'version' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check version format
    m_sVersion = m_yamlPackageInfo["version"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldCMakeMinimumRequired() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("cmake_minimum_required")) {
        WSJCppLog::err(TAG, "Missing required field 'cmake_minimum_required' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check cmake_version format
    m_sCMakeMinimumRequired = m_yamlPackageInfo["cmake_minimum_required"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldCMakeCxxStandard() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("cmake_cxx_standard")) {
        WSJCppLog::err(TAG, "Missing required field 'cmake_cxx_standard' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check cmake_cxx_standard format
    m_sCMakeCxxStandard = m_yamlPackageInfo["cmake_cxx_standard"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldName() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("name")) {
        WSJCppLog::err(TAG, "Missing required field 'name' in " + m_yamlPackageInfo.getRoot()->getForLogFormat());
        return false;
    }
    // TODO: check name format
    m_sName = m_yamlPackageInfo["name"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldDescription() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("description")) {
        WSJCppLog::err(TAG, "Missing required field 'description' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sDescription = m_yamlPackageInfo["description"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldWsjcppVersion() {    
    if (!m_yamlPackageInfo.getRoot()->hasElement("wsjcpp_version")) {
        WSJCppLog::err(TAG, "Missing required field 'wsjcpp_version' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sWSJCppVersion = m_yamlPackageInfo["wsjcpp_version"].getValue();
    // TODO version comparator 
    // if (nWSJCppVersion > m_nWSJCppVersion) {
        //   std::cout << "WARN: Please update your 'wsjcpp' to " << nWSJCppVersion << std::endl;
    // }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldIssues() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("issues")) {
        WSJCppLog::err(TAG, "Missing required field 'issues' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sIssues = m_yamlPackageInfo["issues"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldKeywords() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("keywords")) {
        WSJCppLog::err(TAG, "Missing required field 'keywords' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemKeywords = m_yamlPackageInfo["keywords"];
    int nLength = itemKeywords.getLength();
    for (int i = 0; i < nLength; i++) {
        std::string sKeyword = itemKeywords[i].getValue();
        m_vKeywords.push_back(sKeyword);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldAuthors() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("authors")) {
        WSJCppLog::err(TAG, "Missing required field 'authors' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemAuthors = m_yamlPackageInfo["authors"];
    int nLength = itemAuthors.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlAuthor = itemAuthors.getElement(i);
        WSJCppPackageManagerAuthor author;
        author.fromYAML(pYamlAuthor);
        m_vAuthors.push_back(author);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldDistribution() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("distribution")) {
        WSJCppLog::err(TAG, "Missing required field 'distribution' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemDistribution = m_yamlPackageInfo["distribution"];
    int nLength = itemDistribution.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlSource = itemDistribution.getElement(i);
        WSJCppPackageManagerDistributionFile source;
        source.fromYAML(pYamlSource);
        m_vDistributionFiles.push_back(source);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldOrigins() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("origins")) {
        WSJCppLog::err(TAG, "Missing required field 'origins' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemOrigins = m_yamlPackageInfo["origins"];
    int nLength = itemOrigins.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlOrigins = itemOrigins.getElement(i);
        WSJCppPackageManagerOrigin origin;
        origin.fromYAML(pYamlOrigins);
        m_vOrigins.push_back(origin);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldDependencies() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("dependencies")) {
        WSJCppLog::err(TAG, "Missing required field 'dependencies' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemDependencies = m_yamlPackageInfo["dependencies"];
    int nLength = itemDependencies.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlDependence = itemDependencies.getElement(i);
        WSJCppPackageManagerDependence dependence;
        dependence.fromYAML(pYamlDependence);
        m_vDependencies.push_back(dependence);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldRepositories() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("repositories")) {
        WSJCppLog::err(TAG, "Missing required field 'repositories' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemRepositories = m_yamlPackageInfo["repositories"];
    int nLength = itemRepositories.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlRepository = itemRepositories.getElement(i);
        WSJCppPackageManagerRepository repository;
        repository.fromYAML(pYamlRepository);
        m_vRepositories.push_back(repository);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldUnitTests() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("unit-tests")) {
        WSJCppLog::err(TAG, "Missing required field 'unit-tests' in '" + m_sYamlFullpath + "'");
        return false;
    }

    WSJCppYAMLItem itemUnitTests = m_yamlPackageInfo["unit-tests"];
    if (!itemUnitTests.hasElement("cases")) {
        WSJCppLog::err(TAG, "Missing required field 'cases' in '" + m_sYamlFullpath + "' " + itemUnitTests.getForLogFormat());
        return false;
    }
    WSJCppYAMLItem itemCases = itemUnitTests["cases"];

    int nLength = itemCases.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlCase = itemCases.getElement(i);
        WSJCppPackageManagerUnitTest unitTest;
        unitTest.fromYAML(pYamlCase);
        m_vUnitTests.push_back(unitTest);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldRequiredLibraries() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("required-libraries")) {
        WSJCppLog::err(TAG, "Missing required field 'required-libraries' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemRequiredLibraries = m_yamlPackageInfo["required-libraries"];
    int nLength = itemRequiredLibraries.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlRequredLibrary = itemRequiredLibraries.getElement(i);
        std::string sRequiredLibrary = pYamlRequredLibrary->getValue();
        m_sRequiredLibraries.push_back(sRequiredLibrary);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldRequiredPkgConfig() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("required-pkg-config")) {
        WSJCppLog::err(TAG, "Missing required field 'required-pkg-config' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemRequiredPkgConfig = m_yamlPackageInfo["required-pkg-config"];
    int nLength = itemRequiredPkgConfig.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlRequredPkgConfig = itemRequiredPkgConfig.getElement(i);
        std::string sRequiredPkgConfig = pYamlRequredPkgConfig->getValue();
        m_sRequiredPkgConfig.push_back(sRequiredPkgConfig);
    }
    return true;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::removeDependenciesFilesSafe(const WSJCppPackageManagerDependence &dep) {
    WSJCppPackageManager pkgDep(dep.getInstallationDir(), m_sDir, true);
    if (pkgDep.load()) {
        std::vector<WSJCppPackageManagerDistributionFile> vFiles = pkgDep.getListOfDistributionFiles();
        int nRemovedFiles = 0;
        for (int i = 0; i < vFiles.size(); i++) {
            WSJCppPackageManagerDistributionFile file = vFiles[i];
            std::string sFilePath = dep.getInstallationDir() + "/" + file.getTargetFile();
            if (!WSJCppCore::fileExists(sFilePath)) {
                WSJCppLog::info(TAG, "Did not found file '" + sFilePath + "'");
            } else {
                std::string sContent;
                WSJCppCore::readTextFile(sFilePath, sContent);
                std::string sSha1 = WSJCppHashes::sha1_calc_hex(sContent);
                if (sSha1 != file.getSha1()) {
                    WSJCppLog::warn(TAG, "Could not remove file '" + sFilePath + "', because maybe has local important changes. "
                        "\r\n  sha1 expected '" + file.getSha1() + "', but got '" + sSha1 + "'");
                } else {
                    if (WSJCppCore::removeFile(sFilePath)) {
                        nRemovedFiles++;
                        WSJCppLog::ok(TAG, "Successfully removed '" + sFilePath + "'");
                    }
                }
            }
        }
        if (nRemovedFiles == vFiles.size()) {
            std::string sFilePath = dep.getInstallationDir() + "/wsjcpp.hold.yml";
            if (WSJCppCore::removeFile(sFilePath)) {
                nRemovedFiles++;
                WSJCppLog::ok(TAG, "Successfully removed '" + sFilePath + "'");
            } else {
                WSJCppLog::warn(TAG, "Could not remove '" + sFilePath + "'");
            }

            if (WSJCppCore::removeFile(dep.getInstallationDir())) {
                WSJCppLog::ok(TAG, "Successfully removed directory '" + dep.getInstallationDir() + "'");
            } else {
                WSJCppLog::warn(TAG, "Could not remove directory '" + dep.getInstallationDir() + "'");
            }
        }
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogeneratedFiles_CMakeListsTXT() {
    std::string sCMakeListsTXT = ""
        "# Automaticly generated by wsjcpp@" + m_sWSJCppCurrentVersion + "\n"
        "cmake_minimum_required(VERSION " + m_sCMakeMinimumRequired + ")\n"
        "\n"
        "add_definitions(-DWSJCPP_VERSION=\"" + m_sVersion + "\")\n"
        "add_definitions(-DWSJCPP_NAME=\"" + m_sName + "\")\n"
        "\n"
        "if (${CMAKE_SYSTEM_NAME} MATCHES \"Darwin\")\n"    
        "    set(MACOSX TRUE)\n"
        "endif()\n"
        "\n"
        "set(CMAKE_CXX_STANDARD " + m_sCMakeCxxStandard + ")\n"
        "\n"
        "set (WSJCPP_LIBRARIES \"\")\n"
        "set (WSJCPP_INCLUDE_DIRS \"\")\n"
        "set (WSJCPP_SOURCES \"\")\n"
        "\n"
    ;

    for (int i = 0; i < m_vDependencies.size(); i++) {
        WSJCppPackageManagerDependence dep = m_vDependencies[i];
        std::string sInstDir = dep.getInstallationDir();
        WSJCppPackageManager pkg(dep.getInstallationDir(), m_sDir, true);
        if (pkg.load()) {
            sCMakeListsTXT += 
                "# " + pkg.getName() + ":" + pkg.getVersion() + "\n"
                "list (APPEND WSJCPP_INCLUDE_DIRS \"" + sInstDir + "/\")\n";
            std::vector<WSJCppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
            for (int i = 0; i < vFiles.size(); i++) {
                WSJCppPackageManagerDistributionFile file = vFiles[i];
                if (file.getType() == "source-code") {
                    sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \"" + sInstDir + "/" + file.getTargetFile() + "\")\n";
                }
            }
        }
        sCMakeListsTXT += "\n";
    }
    
    if (m_sRequiredLibraries.size() > 0) {
        sCMakeListsTXT += "# required-libraries\n";
        for (int i = 0; i < m_sRequiredLibraries.size(); i++) {
            std::string sLibrary = m_sRequiredLibraries[i];
            sCMakeListsTXT += "list (APPEND WSJCPP_LIBRARIES \"-l" + sLibrary + "\")\n";
        }
        sCMakeListsTXT += "\n";
    }
    
    if (m_sRequiredPkgConfig.size() > 0) {
        sCMakeListsTXT += "# required-pkg-config\n";
        for (int i = 0; i < m_sRequiredPkgConfig.size(); i++) {
            std::string sPkgConfig = m_sRequiredPkgConfig[i];
            sCMakeListsTXT += 
                "## " + sPkgConfig + "\n"
                "FIND_PACKAGE(" + sPkgConfig + ")\n"
                "IF(" + sPkgConfig + "_FOUND)\n"
                "   list (APPEND WSJCPP_INCLUDE_DIRS ${" + sPkgConfig + "_INCLUDE_DIR})\n"
                "   list (APPEND WSJCPP_LIBRARIES ${" + sPkgConfig + "_LIBRARIES})\n"
                "ELSE(" + sPkgConfig + "_FOUND)\n"
                "   MESSAGE(FATAL_ERROR \"Could not find the " + sPkgConfig + " library and development files.\")\n"
                "ENDIF(" + sPkgConfig + "_FOUND)\n";
        }
        sCMakeListsTXT += "\n";
    }

    WSJCppCore::writeFile("./src.wsjcpp/CMakeLists.txt", sCMakeListsTXT);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogeneratedFiles_Dockerfiles() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("docker")) {
        // Not need if docker section not defined
        return true;
    }

    if (!updateAutogeneratedFiles_Dockerfile_for_build()) {
        return false;
    }

    if (!updateAutogeneratedFiles_Dockerfile_for_release()) {
        return false;
    }

    if (!updateAutogeneratedFiles_Dockerfile_release()) {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogeneratedFiles_Dockerfile_for_build() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("docker")) {
        // Not need if docker section not defined
        return true;
    }

    std::string sContent = 
        "# Automaticly generated by wsjcpp@" + m_sWSJCppCurrentVersion + "\n"
        "# for-build " + m_sName + ":" + m_sVersion + "\n"
        "FROM debian:10\n"
    ;

    std::vector<std::string> vInstallPackagesBuild = {"make", "cmake", "gcc", "g++", "pkg-config" };
    // TODO check equals and from dependencies 
    for (int i = 0; i < m_sDockerPackagesBuild.size(); i++) {
        vInstallPackagesBuild.push_back(m_sDockerPackagesBuild[i]);
    }
    // TODO: packages-build
    sContent += 
        "# install build requiremenets\n"
        "RUN apt-get update && apt-get install -y \\\n";
    for (int i = 0; i < vInstallPackagesBuild.size(); i++) {
        sContent += "  " + vInstallPackagesBuild[i] + "\\\n";
    }
    sContent += 
        "\n"
        "RUN apt-get clean\n"
        "\n"
        "WORKDIR /root/sources\n"
    ;

    if (!WSJCppCore::dirExists("./docker.for-build")) {
        WSJCppCore::makeDir("./docker.for-build");
    }
    WSJCppCore::writeFile("./docker.for-build/Dockerfile", sContent);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogeneratedFiles_Dockerfile_for_release() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("docker")) {
        // Not need if docker section not defined
        return true;
    }

    std::string sContent = 
        "# Automaticly generated by wsjcpp@" + m_sWSJCppCurrentVersion + "\n"
        "# for-release " + m_sName + ":" + m_sVersion + "\n"
        "FROM debian:10\n";

    std::vector<std::string> vInstallPackagesRelease = {"locales", "libpthread-stubs0-dev" };
    // TODO check equals and from dependencies 
    for (int i = 0; i < m_sDockerPackagesRelease.size(); i++) {
        vInstallPackagesRelease.push_back(m_sDockerPackagesRelease[i]);
    }
    // TODO: packages-build
    sContent += 
        "# install release requiremenets\n"
        "RUN apt-get update && apt-get install -y \\\n";
    for (int i = 0; i < vInstallPackagesRelease.size(); i++) {
        sContent += "  " + vInstallPackagesRelease[i] + "\\\n";
    }
    sContent += 
        "\n"
        "RUN sed -i -e \"s/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/\" /etc/locale.gen && \\\n"
        "  echo 'LANG=\"en_US.UTF-8\"'>/etc/default/locale && \\\n"
        "  dpkg-reconfigure --frontend=noninteractive locales && \\\n"
        "  update-locale LANG=en_US.UTF-8\n"
        "\n"
        "RUN apt-get clean\n"
        "\n"
        "WORKDIR /root/\n";

    if (!WSJCppCore::dirExists("./docker.for-release")) {
        WSJCppCore::makeDir("./docker.for-release");
    }
    WSJCppCore::writeFile("./docker.for-release/Dockerfile", sContent);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogeneratedFiles_Dockerfile_release() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("docker")) {
        // Not need if docker section not defined
        return true;
    }
    WSJCppYAMLItem *pItem = m_yamlPackageInfo.getRoot()->getElement("docker");
    if (!pItem->hasElement("release")) {
        // Do nothing if docker/release section not defined
        return true;
    }

    // if has docker/release
    std::string sContent = 
        "# Automaticly generated by wsjcpp@" + m_sWSJCppCurrentVersion + "\n"
        "# for-release " + m_sName + ":" + m_sVersion + "\n"
        "FROM " + m_sName + "-for-build:latest\n"
        "\n"
        "COPY . /root/sources\n"
        "RUN mkdir -p tmp.docker && cd tmp.docker && cmake .. && make\n"
        "\n"
        "FROM " + m_sName + "-for-release:latest\n"
        "\n";

        // TODO labels
        // LABEL "maintainer"="FreeHackQuest Team <freehackquest@gmail.com>"
        // LABEL "repository"="https://github.com/freehackquest/fhq-docker-build"
    sContent += 
        "COPY --from=0 /root/sources/" + m_sName + " /usr/bin/" + m_sName + "\n";
    
    // TODO expose-ports 
    // EXPOSE 1234 4613 7080
    // TODO command
    // CMD wsjcpp start

    WSJCppCore::writeFile("./Dockerfile", sContent);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogeneratedFiles_UnitTests() {
    std::string sUnitTestsDir = "./unit-tests.wsjcpp";
    if (!WSJCppCore::dirExists(sUnitTestsDir)) {
        WSJCppCore::makeDir(sUnitTestsDir);
    }
    if (!WSJCppCore::dirExists(sUnitTestsDir)) {
        WSJCppLog::err(TAG, "Could not create " + sUnitTestsDir + " directory");
        return false;
    }
    
    std::string sGitignore = 
        "tmp/*\n"
        "logs/*\n"
        "unit-tests\n"
        ".wsjcpp/*\n"
        "\n"
        "# Vim temp files\n"
        "*.swp\n"
    ;
        
    WSJCppCore::writeFile(sUnitTestsDir + "/.gitignore", sGitignore);

    std::string sBuildSimpleSH = 
        "#!/bin/bash\n"
        "\n"
        "if [ ! -d tmp ]; then\n"
        "	mkdir -p tmp\n"
        "fi\n"
        "\n"
        "cd tmp\n"
        "cmake ..\n"
        "make\n";

    WSJCppCore::writeFile(sUnitTestsDir + "/build_simple.sh", sBuildSimpleSH);

    std::string sCMakeListsTXT = ""
        "# Automaticly generated by wsjcpp@" + m_sWSJCppCurrentVersion + "\n"
        "cmake_minimum_required(VERSION " + m_sCMakeMinimumRequired + ")\n"
        "\n"
        "project(unit-tests C CXX)\n"
        "add_definitions(-DWSJCPP_VERSION=\"ut-" + m_sVersion + "\")\n"
        "add_definitions(-DWSJCPP_NAME=\"unit-tests-" + m_sName + "\")\n"
        "\n"
        "if (${CMAKE_SYSTEM_NAME} MATCHES \"Darwin\")\n"    
        "    set(MACOSX TRUE)\n"
        "endif()\n"
        "\n"
        "set(CMAKE_CXX_STANDARD " + m_sCMakeCxxStandard + ")\n"
        "set(EXECUTABLE_OUTPUT_PATH ${unit-tests_SOURCE_DIR})\n"
        "\n"
        "set (WSJCPP_LIBRARIES \"\")\n"
        "set (WSJCPP_INCLUDE_DIRS \"\")\n"
        "set (WSJCPP_SOURCES \"\")\n"
        "\n"
        "find_package(Threads REQUIRED)\n"
        "list (APPEND WSJCPP_SOURCES ${CMAKE_THREAD_LIBS_INIT})\n"
        "\n"
    ;

    for (int i = 0; i < m_vDependencies.size(); i++) {
        WSJCppPackageManagerDependence dep = m_vDependencies[i];
        std::string sInstDir = dep.getInstallationDir();
        WSJCppPackageManager pkg(dep.getInstallationDir(), m_sDir, true);
        if (pkg.load()) {
            sCMakeListsTXT += 
                "# " + pkg.getName() + ":" + pkg.getVersion() + "\n"
                "list (APPEND WSJCPP_INCLUDE_DIRS \""
                    + WSJCppCore::doNormalizePath("../" + sInstDir + "/") 
                    + "\")\n";
            std::vector<WSJCppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
            for (int i = 0; i < vFiles.size(); i++) {
                WSJCppPackageManagerDistributionFile file = vFiles[i];
                if (file.getType() == "source-code" || file.getType() == "unit-tests") {
                    sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \""
                        + WSJCppCore::doNormalizePath("../" + sInstDir + "/" + file.getTargetFile()) 
                        + "\")\n";
                }
            }
        }
        sCMakeListsTXT += "\n";
    }

    sCMakeListsTXT += 
        "# " + m_sName + ":" + m_sVersion + "\n"
        "list (APPEND WSJCPP_INCLUDE_DIRS \"../src\")\n";
    for (int i = 0; i < m_vDistributionFiles.size(); i++) {
        WSJCppPackageManagerDistributionFile file = m_vDistributionFiles[i];
        if (file.getType() == "source-code" || file.getType() == "unit-tests") {
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \""
                + WSJCppCore::doNormalizePath("../" + file.getSourceFile())
                + "\")\n";
        }
    }

    sCMakeListsTXT += 
        "\n"
        "# unit-tests\n"
        "list (APPEND WSJCPP_INCLUDE_DIRS \"src\")\n";

    // list of unit-tests files
    for (int i = 0; i < m_vUnitTests.size(); i++) {
        WSJCppPackageManagerUnitTest ut = m_vUnitTests[i];
        std::string sUnitTestName = ut.getName();
        std::string sName = normalizeUnitTestName(sUnitTestName, false);
        std::string sBaseName = this->generateFilenameForUnitTest(sName);
        std::string sFileHeader = "./unit-tests.wsjcpp/src/" + sBaseName + ".h";
        std::string sFileSource = "./unit-tests.wsjcpp/src/" + sBaseName + ".cpp";
        if (WSJCppCore::fileExists(sFileHeader)) {
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \""
                + WSJCppCore::doNormalizePath("../" + sFileHeader)
                + "\")\n";
        } else {
            WSJCppLog::warn(TAG, "Ignored '" + sFileHeader + "' - file did not exists");
        }

        if (WSJCppCore::fileExists(sFileSource)) {
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \""
                + WSJCppCore::doNormalizePath("../" + sFileSource)
                + "\")\n";
        } else {
            WSJCppLog::warn(TAG, "Ignored '" + sFileSource + "' - file did not exists");
        }
    }
    sCMakeListsTXT += "\n";

    if (m_sRequiredLibraries.size() > 0) {
        sCMakeListsTXT += "# required-libraries\n";
        for (int i = 0; i < m_sRequiredLibraries.size(); i++) {
            std::string sLibrary = m_sRequiredLibraries[i];
            sCMakeListsTXT += "list (APPEND WSJCPP_LIBRARIES \"-l" + sLibrary + "\")\n";
        }
        sCMakeListsTXT += "\n";
    }
    
    if (m_sRequiredPkgConfig.size() > 0) {
        sCMakeListsTXT += "# required-pkg-config\n";
        for (int i = 0; i < m_sRequiredPkgConfig.size(); i++) {
            std::string sPkgConfig = m_sRequiredPkgConfig[i];
            sCMakeListsTXT += 
                "## " + sPkgConfig + "\n"
                "FIND_PACKAGE(" + sPkgConfig + ")\n"
                "IF(" + sPkgConfig + "_FOUND)\n"
                "   list (APPEND WSJCPP_INCLUDE_DIRS ${" + sPkgConfig + "_INCLUDE_DIR})\n"
                "   list (APPEND WSJCPP_LIBRARIES ${" + sPkgConfig + "_LIBRARIES})\n"
                "ELSE(" + sPkgConfig + "_FOUND)\n"
                "   MESSAGE(FATAL_ERROR \"Could not find the " + sPkgConfig + " library and development files.\")\n"
                "ENDIF(" + sPkgConfig + "_FOUND)\n";
        }
        sCMakeListsTXT += "\n";
    }

    sCMakeListsTXT += 
        "\n"
        "include_directories(${WSJCPP_INCLUDE_DIRS})\n"
        "\n"
        "add_executable (\"unit-tests\" ${WSJCPP_SOURCES})\n"
        "\n"
        "target_link_libraries(\"unit-tests\" -lpthread ${WSJCPP_LIBRARIES} )\n"
        "\n"
        "install(\n"
        "    TARGETS\n"
        "        \"unit-tests\"\n"
        "    RUNTIME DESTINATION\n"
        "        /usr/bin\n"
        ")\n\n";

    WSJCppCore::writeFile(sUnitTestsDir + "/CMakeLists.txt", sCMakeListsTXT);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogenerateFileUnitTestHeader(const std::string &sUnitTestName) {
    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    if (sName != sUnitTestName) {
        WSJCppLog::warn(TAG, "UnitTest name was normalized '" + sUnitTestName + "' -> '" + sName + "'");
    }
    if (!WSJCppCore::dirExists("./unit-tests.wsjcpp")) {
        WSJCppCore::makeDir("./unit-tests.wsjcpp");
    }
    if (!WSJCppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WSJCppCore::makeDir("./unit-tests.wsjcpp/src/");
    }
    if (!WSJCppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WSJCppLog::err(TAG, "Directory does not exists './unit-tests.wsjcpp/src/'");
        return false;
    }
    std::string sBaseName = this->generateFilenameForUnitTest(sName);
    std::string sFileHeader = "./unit-tests.wsjcpp/src/" + sBaseName + ".h";
    if (WSJCppCore::fileExists(sFileHeader)) {
        WSJCppLog::err(TAG, "File already exists: '" + sFileHeader + "'");
        return false;
    } else {
        std::string sDefine = WSJCppCore::toUpper(sBaseName + "_H");
        std::string sContent = ""
            "#ifndef " + sDefine + "\n"
            "#define " + sDefine + "\n"
            "\n"
            "#include <wsjcpp_unit_tests.h>\n"
            "\n"
            "// Description: TODO\n"
            "class UnitTest" + sName + " : public WSJCppUnitTestBase {\n"
            "    public:\n"
            "        UnitTest" + sName + "();\n"
            "        virtual void init();\n"
            "        virtual bool run();\n"
            "};\n"
            "\n"
            "#endif // " + sDefine + "\n";
        WSJCppCore::writeFile(sFileHeader, sContent);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateAutogenerateFileUnitTestSource(const std::string &sUnitTestName) {
    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    if (sName != sUnitTestName) {
        WSJCppLog::warn(TAG, "UnitTest name was normalized '" + sUnitTestName + "' -> '" + sName + "'");
    }
    if (!WSJCppCore::dirExists("./unit-tests.wsjcpp")) {
        WSJCppCore::makeDir("./unit-tests.wsjcpp");
    }
    if (!WSJCppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WSJCppCore::makeDir("./unit-tests.wsjcpp/src/");
    }
    if (!WSJCppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WSJCppLog::err(TAG, "Directory does not exists './unit-tests.wsjcpp/src/'");
        return false;
    }

    std::string sBaseName = this->generateFilenameForUnitTest(sName);
    std::string sFileSource = "./unit-tests.wsjcpp/src/" + sBaseName + ".cpp";
    if (WSJCppCore::fileExists(sFileSource)) {
        WSJCppLog::err(TAG, "File already exists: '" + sFileSource + "'");
        return false;
    } else {
        std::string sContent = ""
            "#include \"" + sBaseName + ".h\"\n"
            "#include <vector>\n"
            "#include <wsjcpp_core.h>\n"
            // TODO include add current headers
            "\n"
            "REGISTRY_UNIT_TEST(UnitTest" + sName + ")\n"
            "\n"
            "UnitTest" + sName + "::UnitTest" + sName + "()\n"
            "    : WSJCppUnitTestBase(\"UnitTest" + sName + "\") {\n"
            "}\n"
            "\n"
            "// ---------------------------------------------------------------------\n"
            "\n"
            "void UnitTest" + sName + "::init() {\n"
            "    // nothing\n"
            "}\n"
            "\n"
            "// ---------------------------------------------------------------------\n"
            "\n"
            "bool UnitTest" + sName + "::run() {\n"
            "    bool bTestSuccess = true;\n"
            "    compareB(bTestSuccess, \"Not implemented\", true, false);\n"
            "    return bTestSuccess;\n"
            "}\n";
        
        WSJCppCore::writeFile(sFileSource, sContent);
    }
    return true;
}

// ---------------------------------------------------------------------
