#include "wsjcpp_package_manager.h"
#include "wsjcpp_packager_download_dependence.h"
#include <iostream>
#include <fallen.h>
#include <sstream>
#include <fstream>
#include <iomanip>


// ---------------------------------------------------------------------

WSJCppPackageManagerFile::WSJCppPackageManagerFile() {
}

// ---------------------------------------------------------------------

WSJCppPackageManagerFile::WSJCppPackageManagerFile(const std::string &sFile) {
    m_sFrom = sFile;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerFile::getFrom() {
    return m_sFrom;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerFile::getTo() {
    return m_sFrom;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerFile::getSha1() {
    return m_sSha1;
}

// ---------------------------------------------------------------------

nlohmann::json WSJCppPackageManagerFile::toJson() {
    m_jsonFile["from"] = m_sFrom;
    m_jsonFile["to"] = m_sTo;
    m_jsonFile["sha1"] = m_sSha1;
    return m_jsonFile;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerFile::fromJson(const nlohmann::json &jsonFile) {
    m_jsonFile = jsonFile;
    for (auto it = jsonFile.begin(); it != jsonFile.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "from") {
            m_sFrom = it.value();
        } else if (sKey == "to") {
            m_sTo = it.value();
        } else if (sKey == "sha1") {
            m_sSha1 = it.value();
        } else {
           std::cout << "IGNORED in file:  " << sKey << std::endl; 
        }
    }
}

// ---------------------------------------------------------------------

WSJCppPackageManagerAuthor::WSJCppPackageManagerAuthor() {
}

// ---------------------------------------------------------------------

WSJCppPackageManagerAuthor::WSJCppPackageManagerAuthor(const std::string &sName, const std::string &sEmail) {
    m_sName = sName;
    m_sEmail = sEmail;
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

nlohmann::json WSJCppPackageManagerAuthor::toJson() {
    m_jsonAuthor["name"] = m_sName;
    m_jsonAuthor["email"] = m_sEmail;
    return m_jsonAuthor;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerAuthor::fromJson(const nlohmann::json &jsonAuthor) {
    m_jsonAuthor = jsonAuthor;
    for (auto it = jsonAuthor.begin(); it != jsonAuthor.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "name") {
            m_sName = it.value();
        } else if (sKey == "email") {
            m_sEmail = it.value();
        } else {
           std::cout << "IGNORED_AUTHORS in authors:  " << sKey << std::endl; 
        }
    }
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerServer - server info class

WSJCppPackageManagerServer::WSJCppPackageManagerServer() {

}

// ---------------------------------------------------------------------

WSJCppPackageManagerServer::WSJCppPackageManagerServer(const std::string &sAddress) {
    m_sAddress = sAddress;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerServer::getAddress() {
    return m_sAddress;
}

// ---------------------------------------------------------------------

nlohmann::json WSJCppPackageManagerServer::toJson() {
    m_jsonServer["address"] = m_sAddress;
    return m_jsonServer;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerServer::fromJson(const nlohmann::json &jsonServer) {
    m_jsonServer = jsonServer;
    for (auto it = jsonServer.begin(); it != jsonServer.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "address") {
            m_sAddress = it.value();
        } else {
           std::cout << "IGNORED in server:  " << sKey << std::endl; 
        }
    }
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerRepository - repository struct

WSJCppPackageManagerRepository::WSJCppPackageManagerRepository() {
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerRepository::getUrl() {
    return m_sUrl;
}

// ---------------------------------------------------------------------

nlohmann::json WSJCppPackageManagerRepository::toJson() {
    m_jsonRepository["url"] = m_sUrl;
    return m_jsonRepository;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerRepository::fromJson(const nlohmann::json &jsonRepository) {
    m_jsonRepository = jsonRepository;
    for (auto it = jsonRepository.begin(); it != jsonRepository.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "url") {
            m_sUrl = it.value();
        } else {
           std::cout << "IGNORED in repository:  " << sKey << std::endl; 
        }
    }
}

// ---------------------------------------------------------------------
// WSJCppPackageManager - main class

WSJCppPackageManagerDependence::WSJCppPackageManagerDependence() {
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getInstalledDir() {
    return m_sInstalledDir;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getFrom() {
    return m_sFrom;
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

nlohmann::json WSJCppPackageManagerDependence::toJson() {
    m_jsonDependece["type"] = m_sType;
    m_jsonDependece["from"] = m_sFrom;
    m_jsonDependece["name"] = m_sName;
    m_jsonDependece["version"] = m_sVersion;
    return m_jsonDependece;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::fromJson(const nlohmann::json &jsonDependece) {
    m_jsonDependece = jsonDependece;
    for (auto it = jsonDependece.begin(); it != jsonDependece.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "type") {
            m_sType = it.value();
        } else if (sKey == "from") {
            m_sFrom = it.value();
        } else if (sKey == "name") {
            m_sName = it.value();
        } else if (sKey == "version") {
            m_sVersion = it.value();
        } else if (sKey == "installed_dir") {
            m_sInstalledDir = it.value();
        } else {
           std::cout << "IGNORED in dependence:  " << sKey << std::endl; 
        }
    }
}

// ---------------------------------------------------------------------
// WSJCppPackageManager - main class

WSJCppPackageManager::WSJCppPackageManager(const std::string &sDir) {
    TAG = "WSJCppPackageManager";
    m_sDir = sDir;
    m_sDirWithSources = m_sDir + "/src.wsjcpp";
    m_sGithubPrefix = "https://github.com/";
    m_sBitbucketPrefix = "https://bitbucket.com/";
    m_sFilePrefix = "file:///";
    m_sHttpPrefix = "http://";
    m_sHttpsPrefix = "https://";
    m_sWSJCppJsonFilename = "wsjcpp.json";
    m_nWSJCppVersion = 1;
    m_bHolded = false;
}

// ---------------------------------------------------------------------

WSJCppPackageManager::WSJCppPackageManager(const std::string &sDir, const std::string &sParentDir, bool bHolded) 
: WSJCppPackageManager(sDir) {
    m_sDirWithSources = m_sDir + "/src.wsjcpp";
    m_sWSJCppJsonFilename = "wsjcpp.hold.json";
    m_bHolded = true;
    m_sParentDir = sParentDir;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::init() {

    if (!Fallen::dirExists(m_sDir)) {
        std::cout << "Directory '" << m_sDir << "' did not exists... create the dir ? (y/n)" << std::endl;
        std::string sYN;
        std::cin >> sYN;
        if (sYN == "y" || sYN == "Y") {
            Fallen::makeDir(m_sDir);
        }

        if (!Fallen::dirExists(m_sDir)) {
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
        std::cout << "ERROR: wsjcpp is holded" << std::endl;
        return false;
    }
    if (!Fallen::dirExists(m_sDirWithSources)) {
        Fallen::makeDir(m_sDirWithSources);
    }

    std::string sGitkeepFile = m_sDirWithSources + "/.gitkeep";
    if (!Fallen::fileExists(sGitkeepFile)) {
        Fallen::writeFile(sGitkeepFile, "");
    }

    m_jsonPackageInfo["wsjcpp_version"] = m_nWSJCppVersion;
    m_jsonPackageInfo["name"] = m_sName;
    m_jsonPackageInfo["version"] = m_sVersion;
    m_jsonPackageInfo["description"] = m_sDescription;
    m_jsonPackageInfo["keywords"] = m_vKeywords;

    nlohmann::json jsonAuthors = nlohmann::json::array();
    for (int i = 0; i < m_vAuthors.size(); i++) {
        jsonAuthors.push_back(m_vAuthors[i].toJson());
    }
    m_jsonPackageInfo["authors"] = jsonAuthors;

    nlohmann::json jsonServers = nlohmann::json::array();
    for (int i = 0; i < m_vServers.size(); i++) {
        jsonServers.push_back(m_vServers[i].toJson());
    }

    m_jsonPackageInfo["servers"] = jsonServers;

    nlohmann::json jsonDependencies = nlohmann::json::array();
    for (int i = 0; i < m_vDependencies.size(); i++) {
        jsonDependencies.push_back(m_vDependencies[i].toJson());
    }
    m_jsonPackageInfo["deps"] = jsonDependencies;

    nlohmann::json jsonFiles = nlohmann::json::array();
    for (int i = 0; i < m_vFiles.size(); i++) {
        jsonFiles.push_back(m_vFiles[i].toJson());
    }
    m_jsonPackageInfo["files"] = jsonFiles;

    nlohmann::json jsonRepositories = nlohmann::json::array();
    for (int i = 0; i < m_vRepositories.size(); i++) {
        jsonRepositories.push_back(m_vRepositories[i].toJson());
    }
    m_jsonPackageInfo["repositories"] = jsonRepositories;

    int indent = 4;
    std::ofstream cppspmJson(m_sDir + "/" + m_sWSJCppJsonFilename);
    cppspmJson << std::setw(4) << m_jsonPackageInfo << std::endl;
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::load() {
    std::string sJsonFilename = m_sDir + "/" + m_sWSJCppJsonFilename;

    if (!Fallen::fileExists(sJsonFilename)) {
        std::cout << "ERROR: '" << sJsonFilename << "' did not found" << std::endl;
        return false;
    }

    std::ifstream ifs(sJsonFilename);
    m_jsonPackageInfo = nlohmann::json::parse(ifs);

    for (auto it = m_jsonPackageInfo.begin(); it != m_jsonPackageInfo.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "name") {
            m_sName = it.value();
        } else if (sKey == "version") {
            m_sVersion = it.value();
        } else if (sKey == "description") {
            m_sDescription = it.value();
        } else if (sKey == "keywords") {
            nlohmann::json jsonKeywords = it.value();
            for (auto it1 = jsonKeywords.begin(); it1 != jsonKeywords.end(); ++it1) {
                std::string keyword = it1.value();
                m_vKeywords.push_back(keyword);
            }
        } else if (sKey == "wsjcpp_version") {
            int nWSJCppVersion = it.value();
            if (nWSJCppVersion > m_nWSJCppVersion) {
                std::cout << "WARN: Please update your 'cppspm' to " << nWSJCppVersion << std::endl;
            }
        } else if (sKey == "authors") {
            nlohmann::json jsonAuthors = it.value();
            for (auto it2 = jsonAuthors.begin(); it2 != jsonAuthors.end(); ++it2) {
                WSJCppPackageManagerAuthor author;
                author.fromJson(it2.value());
                m_vAuthors.push_back(author);
            }
        } else if (sKey == "files") {
            nlohmann::json jsonFiles = it.value();
            for (auto it3 = jsonFiles.begin(); it3 != jsonFiles.end(); ++it3) {
                WSJCppPackageManagerFile file;
                file.fromJson(it3.value());
                m_vFiles.push_back(file);
            }
        } else if (sKey == "servers") {
            nlohmann::json jsonServers = it.value();
            for (auto it4 = jsonServers.begin(); it4 != jsonServers.end(); ++it4) {
                WSJCppPackageManagerServer server;
                server.fromJson(it4.value());
                m_vServers.push_back(server);
            }
        } else if (sKey == "deps") {
            nlohmann::json jsonDependencies = it.value();
            for (auto it5 = jsonDependencies.begin(); it5 != jsonDependencies.end(); ++it5) {
                WSJCppPackageManagerDependence dependence;
                dependence.fromJson(it5.value());
                m_vDependencies.push_back(dependence);
            }
        } else if (sKey == "reps") {
            nlohmann::json jsonRepositories = it.value();
            for (auto it6 = jsonRepositories.begin(); it6 != jsonRepositories.end(); ++it6) {
                WSJCppPackageManagerRepository repo;
                repo.fromJson(it6.value());
                m_vRepositories.push_back(repo);
            }
        } else {
           std::cout << "IGNORED:  " << sKey << std::endl; 
        }
    }
    return true;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printFiles() {
    for (auto it = m_vFiles.begin(); it != m_vFiles.end(); ++it) {
        std::cout << it->getSha1() << " " << it->getFrom() << " -> " << it->getTo() << std::endl;
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addFile(const std::string &sFile) {
    if (m_bHolded) {
        std::cout << "ERROR: cppspm is holded" << std::endl;
        return false;
    }

    if (!Fallen::fileExists(sFile)) {
        std::cout << "Error: '" << sFile << "' already exists." << std::endl;
        return false;
    }

    for (auto it = m_vFiles.begin(); it != m_vFiles.end(); ++it) {
        if (it->getFrom() == sFile) {
            std::cout << "Error: File '" << sFile << "' already exists." << std::endl;
            return false;
        }
    }

    WSJCppPackageManagerFile file(sFile);
    m_vFiles.push_back(file);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::deleteFile(const std::string &sFile) {
    if (m_bHolded) {
        std::cout << "ERROR: cppspm is holded" << std::endl;
        return false;
    }

    for (auto it = m_vFiles.begin(); it != m_vFiles.end(); ++it) {
        if (it->getFrom() == sFile) {
            m_vFiles.erase(it);
            return true;
        }
    }
    std::cout << "Error: File '" << sFile << "' did not found." << std::endl;
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
        std::cout << "ERROR: cppspm is holded" << std::endl;
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
        std::cout << sIntent << " * " << it->getName() << ":" << it->getVersion() << "    (" << it->getType() << ":" << it->getFrom() << ")" << std::endl;
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
        std::cout << "ERROR: Could not install package when holded" << std::endl;
        return false;
    }
    if (sPackage.compare(0, m_sGithubPrefix.size(), m_sGithubPrefix) == 0) {
        return installFromGithub(sPackage);
    } else if (sPackage.compare(0, m_sBitbucketPrefix.size(), m_sBitbucketPrefix) == 0) {
        // TODO
    } else if (sPackage.compare(0, m_sFilePrefix.size(), m_sFilePrefix) == 0) {
        // TODO
    } else if (
        sPackage.compare(0, m_sHttpPrefix.size(), m_sHttpPrefix) == 0
        || sPackage.compare(0, m_sHttpsPrefix.size(), m_sHttpsPrefix) == 0
    ) {
        // TODO
    }

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
    std::string url = "https://github.com/" + packageName + "/archive/" + packageVersion + ".zip";
    // std::string url = "https://github.com/" + packageName + "/zip/" + packageVersion;
    std::string ufolder = "github_" + this->packageNameToUFolder(packageName);

    WSJCppPackageManagerDependence d;
    nlohmann::json jsonDependence;
    jsonDependence["type"] = "github";
    jsonDependence["version"] = packageVersion;
    jsonDependence["name"] = packageName;
    jsonDependence["from"] = url;
    jsonDependence["ufolder"] = ufolder;
    
    // https://raw.githubusercontent.com/sea-kg/nlohmann_json/master/cppspm.json

    std::string cacheDir = m_sDir + "/.wsjcpp-cache";
    if (!Fallen::dirExists(cacheDir)) {
        Fallen::makeDir(cacheDir);
    }

    std::string zipFile = cacheDir + "/" + ufolder + ".zip";
    if (Fallen::fileExists(zipFile)) {
        // TODO remove file    
    }
    CppSPM::DownloadDependence::downloadZipFromGithub(url, zipFile);

    // TODO download and check package

    d.fromJson(jsonDependence);
    m_vDependencies.push_back(d);

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
    std::cout << "wsjcpp.version = " << m_nWSJCppVersion << std::endl;
    // print keywords
    std::cout << "Keywords: " << std::endl;
    for (unsigned int i = 0; i < m_vKeywords.size(); i++) {
        std::cout << " - " << m_vKeywords[i] << std::endl;
    }
    if (m_vFiles.size() > 0) {
        std::cout << std::endl << "Files: " << std::endl;
        for (unsigned int i = 0; i < m_vFiles.size(); i++) {
            WSJCppPackageManagerFile file = m_vFiles[i];
            std::cout << " - " << file.getFrom() << " -> " << file.getTo() << " [sha1:" << file.getSha1() << "]" << std::endl;
        }
    }
    
    // TODO: print authors
    // TODO: print files
    // TODO: print deps

    std::cout << "===== end: wsjcpp info =====" << std::endl
        << std::endl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printPackages() {
    std::cout << "Packages: " << std::endl;
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        std::cout << " - " << it->getName() << ":" << it->getVersion() << "    (" << it->getType() << ":" << it->getFrom() << ")" << std::endl;
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
        std::string sInstalledDir = dep.getInstalledDir(); 

        if (Fallen::dirExists(dep.getInstalledDir())) {
            WSJCppPackageManager subpkg(sInstalledDir, m_sDir, true);
            Log::info(TAG, "Loading package '" + sInstalledDir + "'");
            if (subpkg.load()) {
                subpkg.printAuthorsTree();
            } else {
                Log::err(TAG, "Could not load package.");
            }
        } else {
            Log::err(TAG, "Not found installed dir: '" + sInstalledDir + "' for package: " + dep.getName() + ":" + dep.getVersion());
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
        Log::err(TAG, "Author already exists");
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
    Log::err(TAG, "Not found this author");
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
