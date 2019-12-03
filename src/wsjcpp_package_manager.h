#ifndef WSJCPP_PACKAGE_MANAGER_H
#define WSJCPP_PACKAGE_MANAGER_H

#include <string>
#include <json.hpp>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------

class WSJCppPackageManagerFile {
    public:
        WSJCppPackageManagerFile();
        WSJCppPackageManagerFile(const std::string &sFile);
        std::string getFrom();
        std::string getTo();
        std::string getSha1();
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonFile);

    private:
        std::string m_sFrom;
        std::string m_sTo;
        std::string m_sSha1;
        nlohmann::json m_jsonFile;

};

// ---------------------------------------------------------------------

class WSJCppPackageManagerAuthor {
    public:
        WSJCppPackageManagerAuthor();
        WSJCppPackageManagerAuthor(const std::string &sName, const std::string &sEmail);
        std::string getName();
        std::string getEmail(); 
        std::string getFullAuthor(); 
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonAuthor);
    private:
        std::string m_sName;
        std::string m_sEmail;
        nlohmann::json m_jsonAuthor;
};

// ---------------------------------------------------------------------

class WSJCppPackageManagerServer {
    public:
        WSJCppPackageManagerServer();
        WSJCppPackageManagerServer(const std::string &sAddress);
        std::string getAddress();

        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonServer);
        
    private:
        std::string m_sAddress;
        nlohmann::json m_jsonServer;
};

// ---------------------------------------------------------------------

class WSJCppPackageManagerRepository {
    public:
        WSJCppPackageManagerRepository();
        std::string getUrl();
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonRepository);

    private:
        std::string m_sUrl;
        nlohmann::json m_jsonRepository;
};

// ---------------------------------------------------------------------

class WSJCppPackageManagerDependence {
    public:
        WSJCppPackageManagerDependence();
        std::string getInstalledDir();
        std::string getType();
        std::string getFrom();
        std::string getName();
        std::string getVersion();
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonDependence);

    private:
        std::string m_sInstalledDir;
        std::string m_sType;
        std::string m_sFrom;
        std::string m_sName;
        std::string m_sVersion;
        nlohmann::json m_jsonDependece;
};

// ---------------------------------------------------------------------

class WSJCppPackageManager {
    public:
        WSJCppPackageManager(const std::string &sDir);
        WSJCppPackageManager(const std::string &sDir, const std::string &sParentDir, bool bHolded);
        bool init();
        bool load();
        bool save();
        void printFiles();
        bool addFile(const std::string &sFromFile, const std::string &sToFile);
        bool removeFile(const std::string &sFromFile);
        void printServers();
        bool addServer(const std::string &sServer);
        bool deleteServer(const std::string &sServer);
        bool updateDependencies();
        void printDependencies(std::string sIntent = "");
        void verify();
        bool install(const std::string &sPackage);
        void printInfo();
        void printPackages();
        void printAuthors();
        void printAuthorsTree();
        bool addAuthor(const std::string &sName, const std::string &sEmail);
        bool removeAuthor(const std::string &sAuthor);

    private:
        std::string TAG;
        std::string packageNameToUFolder(const std::string &sFilename);
        bool installFromGithub(const std::string &sPackage);
        void recursive_printAuthorsTree(std::vector<WSJCppPackageManagerDependence> &vDependencies);

        std::string m_sGithubPrefix;
        std::string m_sBitbucketPrefix;
        std::string m_sFilePrefix;
        std::string m_sHttpPrefix;
        std::string m_sHttpsPrefix;

        std::string m_sDir;
        bool m_bHolded;
        std::string m_sParentDir;
        std::string m_sYamlFilename;
        int m_nWSJCppVersion;
        std::string m_sDirWithSources;
        std::string m_sName;
        std::string m_sVersion;
        std::string m_sDescription;
        std::vector<std::string> m_vKeywords;
        std::vector<WSJCppPackageManagerAuthor> m_vAuthors;
        std::vector<WSJCppPackageManagerServer> m_vServers;
        std::vector<WSJCppPackageManagerDependence> m_vDependencies;
        std::vector<WSJCppPackageManagerFile> m_vDistributionFiles;
        std::vector<WSJCppPackageManagerRepository> m_vRepositories;
        
        nlohmann::json m_jsonPackageInfo;
        WSJCppYAML m_yamlPackageInfo;
};

#endif // WSJCPP_PACKAGE_MANAGER_H
