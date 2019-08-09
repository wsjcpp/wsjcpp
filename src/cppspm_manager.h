#ifndef CPPSPM_MANAGER_H
#define CPPSPM_MANAGER_H

#include <string>
#include <json.hpp>
#include "cppspm_author.h"
#include "cppspm_server.h"
#include "cppspm_dependence.h"
#include "cppspm_file.h"

namespace CppSPM {

class Manager {
    public:
        Manager(const std::string &sDir);
        bool init();
        bool load();
        void save();
        void printFiles();
        bool addFile(const std::string &sFile);
        bool deleteFile(const std::string &sFile);
        void printServers();
        bool addServer(const std::string &sServer);
        bool deleteServer(const std::string &sServer);
    private:
        std::string m_sDir;
        int m_nCppspmVersion;
        std::string m_sDirWithSources;
        std::string m_sName;
        std::string m_sVersion;
        std::string m_sDescription;
        std::vector<std::string> m_vKeywords;
        std::vector<CppSPM::Author> m_vAuthors;
        std::vector<CppSPM::Server> m_vServers;
        std::vector<CppSPM::Dependence> m_vDependencies;
        std::vector<CppSPM::File> m_vFiles;
        
        nlohmann::json m_jsonPackageInfo;
};

} // namespace CppSPM

#endif // CPPSPM_MANAGER_H