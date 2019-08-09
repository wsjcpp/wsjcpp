#include "cppspm_manager.h"
#include <iostream>
#include <fallen.h>
#include <sstream>
#include <fstream>
#include <iomanip>

namespace CppSPM {

Manager::Manager(const std::string &sDir) {
    m_sDir = sDir;
    m_sDirWithSources = m_sDir + "/src.cppspm";
    m_nCppspmVersion = 1;
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

void Manager::save() {

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

    int indent = 4;
    std::ofstream cppspmJson(m_sDir + "/cppspm.json");
    cppspmJson << std::setw(4) << m_jsonPackageInfo << std::endl;
}

// ---------------------------------------------------------------------

bool Manager::load() {

    std::ifstream ifs(m_sDir + "/cppspm.json");
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
            // m_sName = it.value();
            // TODO check 
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
        } else {
           std::cout << "IGNORED:  " << sKey << std::endl; 
        }
    }
    return true;
}

// ---------------------------------------------------------------------

void Manager::printFiles() {
    for (auto it = m_vFiles.begin(); it != m_vFiles.end(); ++it) {
        std::cout << it->getSha1() << " " << it->getName() << std::endl;
    }
}

// ---------------------------------------------------------------------

bool Manager::addFile(const std::string &sFile) {
    if (!Fallen::fileExists(sFile)) {
        std::cout << "Error: cppspm.json already exists." << std::endl;
        return false;
    }

    for (auto it = m_vFiles.begin(); it != m_vFiles.end(); ++it) {
        if (it->getName() == sFile) {
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
    for (auto it = m_vFiles.begin(); it != m_vFiles.end(); ++it) {
        if (it->getName() == sFile) {
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
    for (auto it = m_vServers.begin(); it != m_vServers.end(); ++it) {
        if (it->getAddress() == sServer) {
            m_vServers.erase(it);
            return true;
        }
    }
    std::cout << "Error: Server '" << sServer << "' did not found." << std::endl;
    return false;
}

} // namespace CppSPM