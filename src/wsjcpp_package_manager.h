#ifndef WSJCPP_PACKAGE_MANAGER_H
#define WSJCPP_PACKAGE_MANAGER_H

#include <string>
#include <json.hpp>
#include "wsjcpp_server.h"
#include "wsjcpp_dependence.h"
#include "wsjcpp_file.h"
#include "wsjcpp_repository.h"

class WSJCppPackageManagerAuthor {
    public:
        WSJCppPackageManagerAuthor();
        WSJCppPackageManagerAuthor(const std::string &sName);
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonAuthor);
    private:
        std::string m_sName;
        nlohmann::json m_jsonAuthor;
};


class WSJCppPackageManager {
    public:
        WSJCppPackageManager(const std::string &sDir);
        WSJCppPackageManager(const std::string &sDir, const std::string &sParentDir, bool bHolded);
        bool init();
        bool load();
        bool save();
        void printFiles();
        bool addFile(const std::string &sFile);
        bool deleteFile(const std::string &sFile);
        void printServers();
        bool addServer(const std::string &sServer);
        bool deleteServer(const std::string &sServer);
        bool updateDependencies();
        void printDependencies(std::string sIntent = "");
        void verify();
        bool installFromGithub(const std::string &packageName);

    private:
        std::string packageNameToUFolder(const std::string &sFilename);

        std::string m_sDir;
        bool m_bHolded;
        std::string m_sParentDir;
        std::string m_sCppSPMJsonFilename;
        int m_nCppspmVersion;
        std::string m_sDirWithSources;
        std::string m_sName;
        std::string m_sVersion;
        std::string m_sDescription;
        std::vector<std::string> m_vKeywords;
        std::vector<WSJCppPackageManagerAuthor> m_vAuthors;
        std::vector<CppSPM::Server> m_vServers;
        std::vector<CppSPM::Dependence> m_vDependencies;
        std::vector<CppSPM::File> m_vFiles;
        std::vector<CppSPM::Repository> m_vRepositories;
        
        nlohmann::json m_jsonPackageInfo;
};

#endif // WSJCPP_PACKAGE_MANAGER_H