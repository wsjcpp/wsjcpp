#include "wsjcpp_package_manager.h"
#include "wsjcpp_packager_download_dependence.h"
#include <iostream>
#include <wsjcpp_core.h>
#include <sstream>
#include <fstream>
#include <iomanip>

// ---------------------------------------------------------------------
// WSJCppPackageManagerDistributionSource

WSJCppPackageManagerDistributionSource::WSJCppPackageManagerDistributionSource() {
    TAG = "WSJCppPackageManagerDistributionSource";
}

// ---------------------------------------------------------------------

WSJCppPackageManagerDistributionSource::WSJCppPackageManagerDistributionSource(const std::string &sFile) {
    TAG = "WSJCppPackageManagerDistributionSource";
    m_sFrom = sFile;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerDistributionSource::fromYAML(WSJCppYAMLItem *pYamlDistributionSource) {
    m_pYamlDistributionSource = pYamlDistributionSource;
    if (!m_pYamlDistributionSource->hasElement("from")) {
        WSJCppLog::err(TAG, "Missing required field 'from' in " + m_pYamlDistributionSource->getForLogFormat());
        return false; 
    } else {
        m_sFrom = m_pYamlDistributionSource->getElement("from")->getValue();
    }

    if (!m_pYamlDistributionSource->hasElement("to")) {
        WSJCppLog::err(TAG, "Missing required field 'to' in " + m_pYamlDistributionSource->getForLogFormat());
        return false; 
    } else {
        m_sTo = m_pYamlDistributionSource->getElement("to")->getValue();
    }

    if (!m_pYamlDistributionSource->hasElement("sha1")) {
        WSJCppLog::err(TAG, "Missing required field 'sha1' in " + m_pYamlDistributionSource->getForLogFormat());
        return false; 
    } else {
        m_sSha1 = m_pYamlDistributionSource->getElement("sha1")->getValue();
    }

    return true;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerDistributionSource::toYAML() {
    m_pYamlDistributionSource->getElement("from")->setValue(m_sFrom, true);
    m_pYamlDistributionSource->getElement("to")->setValue(m_sTo, true);
    m_pYamlDistributionSource->getElement("sha1")->setValue(m_sSha1, true);
    return m_pYamlDistributionSource;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionSource::getFrom() {
    return m_sFrom;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionSource::getTo() {
    return m_sTo;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionSource::getSha1() {
    return m_sSha1;
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerDistributionScript

WSJCppPackageManagerDistributionScript::WSJCppPackageManagerDistributionScript() {
    TAG = "WSJCppPackageManagerDistributionScript";
}

// ---------------------------------------------------------------------

WSJCppPackageManagerDistributionScript::WSJCppPackageManagerDistributionScript(const std::string &sFile) {
    TAG = "WSJCppPackageManagerDistributionScript";
    m_sFrom = sFile;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerDistributionScript::fromYAML(WSJCppYAMLItem *pYamlDistributionSource) {
    m_pYamlDistributionScript = pYamlDistributionSource;
    if (!m_pYamlDistributionScript->hasElement("from")) {
        WSJCppLog::err(TAG, "Missing required field 'from' in " + m_pYamlDistributionScript->getForLogFormat());
        return false; 
    } else {
        m_sFrom = m_pYamlDistributionScript->getElement("from")->getValue();
    }

    if (!m_pYamlDistributionScript->hasElement("to")) {
        WSJCppLog::err(TAG, "Missing required field 'to' in " + m_pYamlDistributionScript->getForLogFormat());
        return false; 
    } else {
        m_sTo = m_pYamlDistributionScript->getElement("to")->getValue();
    }

    if (!m_pYamlDistributionScript->hasElement("sha1")) {
        WSJCppLog::err(TAG, "Missing required field 'sha1' in " + m_pYamlDistributionScript->getForLogFormat());
        return false; 
    } else {
        m_sSha1 = m_pYamlDistributionScript->getElement("sha1")->getValue();
    }

    return true;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerDistributionScript::toYAML() {
    m_pYamlDistributionScript->getElement("from")->setValue(m_sFrom, true);
    m_pYamlDistributionScript->getElement("to")->setValue(m_sTo, true);
    m_pYamlDistributionScript->getElement("sha1")->setValue(m_sSha1, true);
    return m_pYamlDistributionScript;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionScript::getFrom() {
    return m_sFrom;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionScript::getTo() {
    return m_sTo;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionScript::getSha1() {
    return m_sSha1;
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
// WSJCppPackageManagerServer - server info class

WSJCppPackageManagerServer::WSJCppPackageManagerServer() {
    TAG = "WSJCppPackageManagerServer";
}

// ---------------------------------------------------------------------

WSJCppPackageManagerServer::WSJCppPackageManagerServer(const std::string &sAddress) {
    TAG = "WSJCppPackageManagerServer";
    m_sAddress = sAddress;
    m_pYamlServer = nullptr;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerServer::toYAML() {
    m_pYamlServer->setValue(m_sAddress, true);
    return m_pYamlServer;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerServer::fromYAML(WSJCppYAMLItem *pYaml) {
    m_pYamlServer = pYaml;
    m_sAddress = m_pYamlServer->getValue();
    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerServer::getAddress() {
    return m_sAddress;
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
// WSJCppPackageManager - main class

WSJCppPackageManagerDependence::WSJCppPackageManagerDependence() {
    TAG = "WSJCppPackageManagerDependence";
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerDependence::toYAML() {
    m_pYamlDependece->getElement("url")->setValue(m_sUrl, true);
    m_pYamlDependece->getElement("name")->setValue(m_sName, true);
    m_pYamlDependece->getElement("version")->setValue(m_sVersion, true);
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

std::string WSJCppPackageManagerDependence::getInstallationDir() {
    return m_sInstallationDir;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getUrl() {
    return m_sUrl;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getVersion() {
    return m_sVersion;
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
    m_sParentDir = sParentDir;
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
    WSJCppPackageManagerServer server(sServerAddress);
    m_vServers.push_back(server);

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

    /* 
    m_jsonPackageInfo["wsjcpp_version"] = m_sWSJCppVersion;
    m_jsonPackageInfo["name"] = m_sName;
    m_jsonPackageInfo["version"] = m_sVersion;
    m_jsonPackageInfo["description"] = m_sDescription;
    m_jsonPackageInfo["keywords"] = m_vKeywords;

    nlohmann::json jsonAuthors = nlohmann::json::array();
    for (int i = 0; i < m_vAuthors.size(); i++) {
        jsonAuthors.push_back(m_vAuthors[i].toJson());
    }
    // m_jsonPackageInfo["authors"] = jsonAuthors;

    nlohmann::json jsonServers = nlohmann::json::array();
    for (int i = 0; i < m_vServers.size(); i++) {
        jsonServers.push_back(m_vServers[i].toJson());
    }

    m_jsonPackageInfo["servers"] = jsonServers;

    nlohmann::json jsonDependencies = nlohmann::json::array();
    for (int i = 0; i < m_vDependencies.size(); i++) {
        jsonDependencies.push_back(m_vDependencies[i].toJson());
    }
    m_jsonPackageInfo["dependencies"] = jsonDependencies;

    nlohmann::json jsonRepositories = nlohmann::json::array();
    for (int i = 0; i < m_vRepositories.size(); i++) {
        jsonRepositories.push_back(m_vRepositories[i].toJson());
    }
    m_jsonPackageInfo["repositories"] = jsonRepositories;

    int indent = 4;
    std::ofstream cppspmJson(m_sDir + "/" + m_sYamlFilename);
    cppspmJson << std::setw(4) << m_jsonPackageInfo << std::endl;
    */
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
        } else if (sKey == "cmake_version") {
            if (!readFieldCMakeVersion()) {
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
        } else if (sKey == "servers") {
            if (!readFieldServers()) {
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

void WSJCppPackageManager::printFiles() {
    for (auto it = m_vDistributionSources.begin(); it != m_vDistributionSources.end(); ++it) {
        std::cout << it->getSha1() << " " << it->getFrom() << " -> " << it->getTo() << std::endl;
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addFile(const std::string &sFromFile, const std::string &sToFile) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WSJCppCore::fileExists(sFromFile)) {
        WSJCppLog::err(TAG, "'" + sFromFile + "' file does not exists");
        return false;
    }

    for (auto it = m_vDistributionSources.begin(); it != m_vDistributionSources.end(); ++it) {
        if (it->getFrom() == sFromFile) {
            WSJCppLog::err(TAG, "This package already contained file '" + sFromFile + "'");
            return false;
        }
    }

    WSJCppPackageManagerDistributionSource source(sFromFile);
    m_vDistributionSources.push_back(source);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::removeFile(const std::string &sFromFile) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    for (auto it = m_vDistributionSources.begin(); it != m_vDistributionSources.end(); ++it) {
        if (it->getFrom() == sFromFile) {
            m_vDistributionSources.erase(it);
            return true;
        }
    }
    WSJCppLog::err(TAG, "Distribution source '" + sFromFile + "' cound not found in this package");
    return false;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printServers() {
    for (auto it = m_vServers.begin(); it != m_vServers.end(); ++it) {
        std::cout << it->getAddress() << std::endl;
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addServer(const std::string &sServer) {
    if (m_bHolded) {
        std::cout << "ERROR: package is holded" << std::endl;
        return false;
    }

    for (auto it = m_vServers.begin(); it != m_vServers.end(); ++it) {
        if (it->getAddress() == sServer) {
            std::cout << "Error: Server '" << sServer << "' already defined." << std::endl;
            return false;
        }
    }

    WSJCppPackageManagerServer server(sServer);
    m_vServers.push_back(server);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::deleteServer(const std::string &sServer) {
    if (m_bHolded) {
        std::cout << "ERROR: cppspm is holded" << std::endl;
        return false;
    }

    for (auto it = m_vServers.begin(); it != m_vServers.end(); ++it) {
        if (it->getAddress() == sServer) {
            m_vServers.erase(it);
            return true;
        }
    }
    std::cout << "Error: Server '" << sServer << "' did not found." << std::endl;
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateDependencies() {
    if (m_bHolded) {
        std::cout << "ERROR: cppspm is holded" << std::endl;
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printDependencies(std::string sIntent) {
    std::string sNexIntent = sIntent + "  \\--";
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        std::cout << sIntent << " * " << it->getName() << ":" << it->getVersion() << "    (" << it->getUrl() << ":" << it->getInstallationDir() << ")" << std::endl;
        if (m_bHolded) {
            WSJCppPackageManager m(m_sParentDir + "/" + it->getName(), m_sParentDir, true);
            if (m.load()) {
                m.printDependencies(sNexIntent);
            }
        } else {
            WSJCppPackageManager m(m_sDirWithSources + "/" + it->getName(), m_sDirWithSources, true);
            if (m.load()) {
                m.printDependencies(sNexIntent);
            }
        }
        
    }
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

    if (sPackage.compare(0, m_sGithubPrefix.size(), m_sGithubPrefix) == 0) {
        return installFromGithub(sPackage);
    } else if (sPackage.compare(0, m_sBitbucketPrefix.size(), m_sBitbucketPrefix) == 0) {
        // TODO
        WSJCppLog::err(TAG, "Could not install package from bitbucket - not implemented yet");
        return false;
    } else if (sPackage.compare(0, m_sFilePrefix.size(), m_sFilePrefix) == 0) {
        // TODO
        WSJCppLog::err(TAG, "Could not install package from file - not implemented yet");
        return false;
    } else if (
        sPackage.compare(0, m_sHttpPrefix.size(), m_sHttpPrefix) == 0
        || sPackage.compare(0, m_sHttpsPrefix.size(), m_sHttpsPrefix) == 0
    ) {
        // TODO
        WSJCppLog::err(TAG, "Could not install package from http(s) - not implemented yet");
        return false;
    }

    WSJCppLog::err(TAG, "Could not install package from unknown source");
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::installFromGithub(const std::string &sPackage) {
    
    if (m_bHolded) { // readonly
        return false;
    }

    std::cout << "Installing package from https://github.com/ ..." << std::endl;
    std::cout << "m_sGithubPrefix: " << m_sGithubPrefix << std::endl;

    std::string sPackageGithubPath = sPackage.substr(m_sGithubPrefix.size());
    std::cout << "sPackageGithubPath: " << sPackageGithubPath << std::endl;
    std::istringstream f(sPackageGithubPath);
    std::string packageName = "";
    std::string s;
    if (getline(f, s, ':')) {
        packageName = s;
    }
    std::string packageVersion = sPackageGithubPath.substr(packageName.size()+1);
    std::string sWsjcppUrl = "https://raw.githubusercontent.com/" + packageName + "/" + packageVersion + "/wsjcpp.json";
    std::cout << "sWsjcppUrl: " << sWsjcppUrl << std::endl;

    std::string url = "https://github.com/" + packageName + "/archive/" + packageVersion + ".zip";
    // std::string url = "https://github.com/" + packageName + "/zip/" + packageVersion;
    std::string ufolder = "github_" + this->packageNameToUFolder(packageName);

    // https://raw.githubusercontent.com/sea-kg/nlohmann_json/v3.7.0/cppspm.json

    WSJCppPackageManagerDependence d;
    nlohmann::json jsonDependence;
    jsonDependence["type"] = "github";
    jsonDependence["version"] = packageVersion;
    jsonDependence["name"] = packageName;
    jsonDependence["from"] = url;
    jsonDependence["ufolder"] = ufolder;
    
    // https://raw.githubusercontent.com/sea-kg/nlohmann_json/master/cppspm.json

    std::string cacheDir = m_sDir + "/.wsjcpp-cache";
    if (!WSJCppCore::dirExists(cacheDir)) {
        WSJCppCore::makeDir(cacheDir);
    }

    std::string zipFile = cacheDir + "/" + ufolder + ".zip";
    if (WSJCppCore::fileExists(zipFile)) {
        // TODO remove file    
    }
    CppSPM::DownloadDependence::downloadZipFromGithub(url, zipFile);

    // TODO download and check package

    // d.fromJson(jsonDependence);
    // m_vDependencies.push_back(d);

    return true;
}

// ---------------------------------------------------------------------

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
    if (m_vDistributionSources.size() > 0) {
        std::cout << std::endl << "Distribution-Files: " << std::endl;
        for (unsigned int i = 0; i < m_vDistributionSources.size(); i++) {
            WSJCppPackageManagerDistributionSource source = m_vDistributionSources[i];
            std::cout << " - " << source.getFrom() << " -> " << source.getTo() << " [sha1:" << source.getSha1() << "]" << std::endl;
        }
    }
    
    // TODO: print authors
    // TODO: print deps

    std::cout << "===== end: wsjcpp info =====" << std::endl
        << std::endl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printPackages() {
    std::cout << "Dependencies: " << std::endl;
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        std::cout << " - " << it->getName() << ":" << it->getVersion() << "    (" << it->getUrl() << " -> " << it->getInstallationDir() << ")" << std::endl;
    }
    std::cout << std::endl;
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

std::string WSJCppPackageManager::packageNameToUFolder(const std::string &sFilename) {
    std::string ret = sFilename;
    std::string illegalChars = "\\/:?\"<>|";
    std::string::iterator it;
    for (it = ret.begin(); it < ret.end() ; ++it) {
        if (illegalChars.find(*it) != std::string::npos) {
            *it = '_';
        }
    }
    return ret;
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

bool WSJCppPackageManager::readFieldCMakeVersion() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("cmake_version")) {
        WSJCppLog::err(TAG, "Missing required field 'cmake_version' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check cmake_version format
    m_sVersion = m_yamlPackageInfo["cmake_version"].getValue();
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
        //   std::cout << "WARN: Please update your 'cppspm' to " << nWSJCppVersion << std::endl;
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
    if (itemDistribution.hasElement("sources")) {
        WSJCppYAMLItem *pItemSources = itemDistribution.getElement("sources");
        int nLength = pItemSources->getLength();
        for (int i = 0; i < nLength; i++) {
            WSJCppYAMLItem *pYamlSource = pItemSources->getElement(i);
            WSJCppPackageManagerDistributionSource source;
            source.fromYAML(pYamlSource);
            m_vDistributionSources.push_back(source);
        }
    }

    if (itemDistribution.hasElement("scripts")) {
        WSJCppYAMLItem *pItemScripts = itemDistribution.getElement("scripts");
        int nLength = pItemScripts->getLength();
        for (int i = 0; i < nLength; i++) {
            WSJCppYAMLItem *pYamlSource = pItemScripts->getElement(i);
            WSJCppPackageManagerDistributionScript script;
            script.fromYAML(pYamlSource);
            m_vDistributionScripts.push_back(script);
        }
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldServers() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("servers")) {
        WSJCppLog::err(TAG, "Missing required field 'servers' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemServers = m_yamlPackageInfo["servers"];
    int nLength = itemServers.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlServer = itemServers.getElement(i);
        WSJCppPackageManagerServer server;
        server.fromYAML(pYamlServer);
        m_vServers.push_back(server);
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