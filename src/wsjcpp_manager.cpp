#include "wsjcpp_manager.h"
#include "wsjcpp_download_dependence.h"
#include <iostream>
#include <fallen.h>
#include <sstream>
#include <fstream>
#include <iomanip>

namespace CppSPM {

Manager::Manager(const std::string &sDir) {
    m_sDir = sDir;
    m_sDirWithSources = m_sDir + "/src.cppspm";
    m_sCppSPMJsonFilename = "cppspm.json";
    m_nCppspmVersion = 1;
    m_bHolded = false;
}

// ---------------------------------------------------------------------

Manager::Manager(const std::string &sDir, const std::string &sParentDir, bool bHolded) {
    m_sDir = sDir;
    m_sDirWithSources = m_sDir + "/src.cppspm";
    m_sCppSPMJsonFilename = "cppspm.hold.json";
    m_nCppspmVersion = 1;
    m_bHolded = true;
    m_sParentDir = sParentDir;
}

// ---------------------------------------------------------------------

bool Manager::init() {

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
    
    std::string sNameOfAuthor = "";
    std::cout << "Author's Name: ";
    std::getline(std::cin, sNameOfAuthor);

    Author author(sNameOfAuthor);
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
    Server server(sServerAddress);
    m_vServers.push_back(server);

    return true;
}

// ---------------------------------------------------------------------

bool Manager::save() {
    if (m_bHolded) {
        std::cout << "ERROR: cppspm is holded" << std::endl;
        return false;
    }
    if (!Fallen::dirExists(m_sDirWithSources)) {
        Fallen::makeDir(m_sDirWithSources);
    }

    std::string sGitkeepFile = m_sDirWithSources + "/.gitkeep";
    if (!Fallen::fileExists(sGitkeepFile)) {
        Fallen::writeFile(sGitkeepFile, "");
    }

    m_jsonPackageInfo["cppspm_version"] = m_nCppspmVersion;
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
    m_jsonPackageInfo["dependencies"] = jsonDependencies;

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
    std::ofstream cppspmJson(m_sDir + "/" + m_sCppSPMJsonFilename);
    cppspmJson << std::setw(4) << m_jsonPackageInfo << std::endl;
    return true;
}

// ---------------------------------------------------------------------

bool Manager::load() {
    std::string sJsonFilename = m_sDir + "/" + m_sCppSPMJsonFilename;

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
        } else if (sKey == "cppspm_version") {
            int nCppSPMVersion = it.value();
            if (nCppSPMVersion > m_nCppspmVersion) {
                std::cout << "WARN: Please update your 'cppspm' to " << nCppSPMVersion << std::endl;
            }
        } else if (sKey == "authors") {
            nlohmann::json jsonAuthors = it.value();
            for (auto it2 = jsonAuthors.begin(); it2 != jsonAuthors.end(); ++it2) {
                CppSPM::Author author;
                author.fromJson(it2.value());
                m_vAuthors.push_back(author);
            }
        } else if (sKey == "files") {
            nlohmann::json jsonFiles = it.value();
            for (auto it3 = jsonFiles.begin(); it3 != jsonFiles.end(); ++it3) {
                CppSPM::File file;
                file.fromJson(it3.value());
                m_vFiles.push_back(file);
            }
        } else if (sKey == "servers") {
            nlohmann::json jsonServers = it.value();
            for (auto it4 = jsonServers.begin(); it4 != jsonServers.end(); ++it4) {
                CppSPM::Server server;
                server.fromJson(it4.value());
                m_vServers.push_back(server);
            }
        } else if (sKey == "dependencies") {
            nlohmann::json jsonDependencies = it.value();
            for (auto it5 = jsonDependencies.begin(); it5 != jsonDependencies.end(); ++it5) {
                CppSPM::Dependence dependence;
                dependence.fromJson(it5.value());
                m_vDependencies.push_back(dependence);
            }
        } else if (sKey == "repositories") {
            nlohmann::json jsonRepositories = it.value();
            for (auto it6 = jsonRepositories.begin(); it6 != jsonRepositories.end(); ++it6) {
                CppSPM::Repository repo;
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

void Manager::printFiles() {
    for (auto it = m_vFiles.begin(); it != m_vFiles.end(); ++it) {
        std::cout << it->getSha1() << " " << it->getFrom() << " -> " << it->getTo() << std::endl;
    }
}

// ---------------------------------------------------------------------

bool Manager::addFile(const std::string &sFile) {
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

    CppSPM::File file(sFile);
    m_vFiles.push_back(file);
    return true;
}

// ---------------------------------------------------------------------

bool Manager::deleteFile(const std::string &sFile) {
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

void Manager::printServers() {
    for (auto it = m_vServers.begin(); it != m_vServers.end(); ++it) {
        std::cout << it->getAddress() << std::endl;
    }
}

// ---------------------------------------------------------------------

bool Manager::addServer(const std::string &sServer) {
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

    CppSPM::Server server(sServer);
    m_vServers.push_back(server);
    return true;
}

// ---------------------------------------------------------------------

bool Manager::deleteServer(const std::string &sServer) {
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

bool Manager::updateDependencies() {
    if (m_bHolded) {
        std::cout << "ERROR: cppspm is holded" << std::endl;
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

void Manager::printDependencies(std::string sIntent) {
    std::string sNexIntent = sIntent + "  \\--";
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        std::cout << sIntent << " * " << it->getName() << ":" << it->getVersion() << "    (" << it->getType() << ":" << it->getFrom() << ")" << std::endl;
        if (m_bHolded) {
            CppSPM::Manager m(m_sParentDir + "/" + it->getName(), m_sParentDir, true);
            if (m.load()) {
                m.printDependencies(sNexIntent);
            }
        } else {
            CppSPM::Manager m(m_sDirWithSources + "/" + it->getName(), m_sDirWithSources, true);
            if (m.load()) {
                m.printDependencies(sNexIntent);
            }
        }
        
    }
}

// ---------------------------------------------------------------------

void Manager::verify() {
    std::vector<std::string> m_vVerified;

    // HERE verify current package
    
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        if (m_bHolded) {
            CppSPM::Manager m(m_sParentDir + "/" + it->getName(), m_sParentDir, true);
            if (m.load()) {
                m.verify();
            }
        } else {
            CppSPM::Manager m(m_sDirWithSources + "/" + it->getName(), m_sDirWithSources, true);
            if (m.load()) {
                m.verify();
            }
        }
        
    }
}

// ---------------------------------------------------------------------

bool Manager::installFromGithub(const std::string &githubPackage) {
    if (m_bHolded) { // readonly
        return false;
    }
    
    std::istringstream f(githubPackage);
    std::string packageName = "";
    std::string s;
    if (getline(f, s, ':')) {
        packageName = s;
    }
    std::string packageVersion = githubPackage.substr(packageName.size()+1);
    std::string url = "https://github.com/" + packageName + "/archive/" + packageVersion + ".zip";
    // std::string url = "https://github.com/" + packageName + "/zip/" + packageVersion;
    std::string ufolder = "github_" + this->packageNameToUFolder(packageName);

    CppSPM::Dependence d;
    nlohmann::json jsonDependence;
    jsonDependence["type"] = "github";
    jsonDependence["version"] = packageVersion;
    jsonDependence["name"] = packageName;
    jsonDependence["from"] = url;
    jsonDependence["ufolder"] = ufolder;
    
    // https://raw.githubusercontent.com/sea-kg/nlohmann_json/master/cppspm.json

    std::string cacheDir = m_sDir + "/.cppspm-cache";
    if (!Fallen::dirExists(cacheDir)) {
        Fallen::makeDir(cacheDir);
    }

    std::string zipFile = cacheDir + "/" + ufolder + ".zip";
    if (Fallen::fileExists(zipFile)) {
        // TODO remove file    
    }
    DownloadDependence::downloadZipFromGithub(url, zipFile);

    // TODO download and check package

    d.fromJson(jsonDependence);
    m_vDependencies.push_back(d);

    return true;
}

// ---------------------------------------------------------------------

std::string Manager::packageNameToUFolder(const std::string &sFilename) {
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

} // namespace CppSPM