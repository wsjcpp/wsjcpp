
#ifndef WSJCPP_PACKAGE_MANAGER_H
#define WSJCPP_PACKAGE_MANAGER_H

#include <string>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------

class WSJCppPackageManagerDistributionFile {
    public:
        WSJCppPackageManagerDistributionFile();
        bool fromYAML(WSJCppYAMLItem *pYamlDistributionFile);
        WSJCppYAMLItem *toYAML();

        std::string getSourceFile();
        std::string getTargetFile();
        std::string getSha1();
        std::string getType();

        void setSourceFile(const std::string &sSourceFile);
        void setTargetFile(const std::string &sTargetFile);
        void setSha1(const std::string &sSha1);
        void setType(const std::string &sType);

    private:
        std::string TAG;
        std::string m_sSourceFile;
        std::string m_sTargetFile;
        std::string m_sSha1;
        std::string m_sType;
        WSJCppYAMLItem *m_pYamlDistributionFile;
};

// ---------------------------------------------------------------------

class WSJCppPackageManagerAuthor {
    public:
        WSJCppPackageManagerAuthor();
        WSJCppPackageManagerAuthor(const std::string &sName, const std::string &sEmail);
        bool fromYAML(WSJCppYAMLItem *pYamlAuthor);
        WSJCppYAMLItem *toYAML();

        std::string getName();
        std::string getEmail(); 
        std::string getFullAuthor(); 

    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sEmail;
        WSJCppYAMLItem *m_pYamlAuthor;
};

// ---------------------------------------------------------------------

class WSJCppPackageManagerOrigin {
    public:
        WSJCppPackageManagerOrigin();
        bool fromYAML(WSJCppYAMLItem *pYaml);
        WSJCppYAMLItem *toYAML();

        std::string getAddress();
        std::string getType();

        void setAddress(const std::string &sAddress);
        void setType(const std::string &sType);
        
    private:
        std::string TAG;
        std::string m_sAddress;
        std::string m_sType;
        WSJCppYAMLItem *m_pYamlOrigin;
};

// ---------------------------------------------------------------------

class WSJCppPackageManagerRepository {
    public:
        WSJCppPackageManagerRepository();
        WSJCppYAMLItem *toYAML();
        bool fromYAML(WSJCppYAMLItem *pYaml);
        std::string getType();
        std::string getUrl();

    private:
        std::string TAG;
        std::string m_sType;
        std::string m_sUrl;
        WSJCppYAMLItem *m_pYamlRepository;
};

// ---------------------------------------------------------------------

class WSJCppPackageManagerUnitTest {
    public:
        WSJCppPackageManagerUnitTest();
        WSJCppYAMLItem *toYAML();
        bool fromYAML(WSJCppYAMLItem *pYaml);
        std::string getName();
        std::string getDescription();
        void setName(const std::string &sName);
        void setDescription(const std::string &sDescription);

    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sDescription;
        WSJCppYAMLItem *m_pYamlUnitTest;
};

// ---------------------------------------------------------------------

class WSJCppPackageManagerDependence {
    public:
        WSJCppPackageManagerDependence();
        std::string getInstallationDir() const;
        std::string getUrl() const;
        std::string getName() const;
        std::string getVersion() const;
        std::string getOrigin() const;
            
        void setName(const std::string &sName);
        void setVersion(const std::string &sVersion);
        void setUrl(const std::string &sUrl);
        void setInstallationDir(const std::string &sInstallationDir);
        void setOrigin(const std::string &sOrigin);

        bool fromYAML(WSJCppYAMLItem *pYaml);
        WSJCppYAMLItem *toYAML();

    private:
        std::string TAG;
        std::string m_sInstallationDir;
        std::string m_sUrl;
        std::string m_sName;
        std::string m_sVersion;
        std::string m_sOrigin;
        WSJCppYAMLItem *m_pYamlDependece;
};

// ---------------------------------------------------------------------

class WSJCppPackageManager {
    public:
        WSJCppPackageManager(const std::string &sDir);
        WSJCppPackageManager(const std::string &sDir, const std::string &sParentDir, bool bHolded);
        std::string getDir() const;
        bool isHolded() const;
        bool init();
        bool load();
        bool save();
        void printFiles();
        bool addSourceFile(const std::string &sSourceFile, const std::string &sTargetFile, const std::string &sType);
        bool removeSourceFile(const std::string &sSourceFile);
        bool updateSourceFile(const std::string &sSourceFile);
        bool createUnitTest(const std::string &sUnitTestName, const std::string &sUnitTestDescription);
        bool deleteUnitTest(const std::string &sUnitTestName);
        bool addOrigin(const std::string &sAddress);
        bool deleteOrigin(const std::string &sAddress);
        bool updateDependencies();
        void verify();
        bool install(const std::string &sPackageUrl);
        bool reinstall(const std::string &sPackageUrl);
        bool uninstall(const std::string &sPackageUrl);
        void printInfo();
        void printAuthors();
        void printAuthorsTree();
        bool addAuthor(const std::string &sName, const std::string &sEmail);
        bool removeAuthor(const std::string &sAuthor);
        std::vector<WSJCppPackageManagerDistributionFile> getListOfDistributionFiles();
        std::vector<WSJCppPackageManagerDependence> getListOfDependencies();
        std::vector<WSJCppPackageManagerUnitTest> getListOfUnitTests();
        std::vector<WSJCppPackageManagerOrigin> getListOfOrigins();
        std::string getName();
        std::string getVersion();

        std::string normalizeUnitTestName(const std::string &sUnitTestName, bool bSilent);
        std::string generateFilenameForUnitTest(const std::string &sUnitTestName);

        bool updateAutogeneratedFiles();

    private:
        std::string TAG;
        bool isGitHubPackage(const std::string &sPackage);
        bool isBitbucketPackage(const std::string &sPackage);
        bool isFilePackage(const std::string &sPackage);
        bool isHttpPackage(const std::string &sPackage);
        bool isHttpsPackage(const std::string &sPackage);

        void addDependency(WSJCppPackageManagerDependence &dep);
        void updateDependency(WSJCppPackageManagerDependence &dep);

        std::string prepareCacheSubFolderName(const std::string &sFilename);
        bool downloadFromGithubToCache(const std::string &sPackage, WSJCppPackageManagerDependence &dep);
        bool isInstalled(const std::string &sPackage);
        bool installFromCache(const std::string &sPackage, const WSJCppPackageManagerDependence &dep);
        bool downloadFileOverHttps(const std::string &sUrl, const std::string &sPath);
        void recursive_printAuthorsTree(std::vector<WSJCppPackageManagerDependence> &vDependencies);
        bool readFieldVersion();
        bool readFieldCMakeMinimumRequired();
        bool readFieldCMakeCxxStandard();
        bool readFieldName();
        bool readFieldDescription();
        bool readFieldWsjcppVersion();
        bool readFieldIssues();
        bool readFieldKeywords();
        bool readFieldAuthors();
        bool readFieldDistribution();
        bool readFieldOrigins();
        bool readFieldDependencies();
        bool readFieldRepositories();
        bool readFieldUnitTests();
        bool readFieldRequiredLibraries();
        bool readFieldRequiredPkgConfig();

        void removeDependenciesFilesSafe(const WSJCppPackageManagerDependence &dep);
        bool updateAutogeneratedFiles_CMakeListsTXT();
        bool updateAutogeneratedFiles_Dockerfiles();
        bool updateAutogeneratedFiles_Dockerfile_for_build();
        bool updateAutogeneratedFiles_Dockerfile_for_release();
        bool updateAutogeneratedFiles_Dockerfile_release();
        bool updateAutogeneratedFiles_UnitTests();
        bool updateAutogenerateFileUnitTestHeader(const std::string &sUnitTestName);
        bool updateAutogenerateFileUnitTestSource(const std::string &sUnitTestName);

        std::string m_sGithubPrefix;
        std::string m_sBitbucketPrefix;
        std::string m_sFilePrefix;
        std::string m_sHttpPrefix;
        std::string m_sHttpsPrefix;

        std::string m_sDir;
        bool m_bHolded;
        std::string m_sParentDir;
        std::string m_sYamlFilename;
        std::string m_sYamlFullpath;
        std::string m_sWSJCppCurrentVersion;
        std::string m_sWSJCppVersion;
        std::string m_sDirWithSources;
        std::string m_sName;
        std::string m_sIssues;
        std::string m_sVersion;
        std::string m_sDescription;
        std::string m_sCMakeMinimumRequired;
        std::string m_sCMakeCxxStandard;
        
        std::vector<std::string> m_vKeywords;
        std::vector<WSJCppPackageManagerAuthor> m_vAuthors;
        std::vector<WSJCppPackageManagerDependence> m_vDependencies;
        std::vector<WSJCppPackageManagerDistributionFile> m_vDistributionFiles;
        std::vector<WSJCppPackageManagerRepository> m_vRepositories;
        std::vector<WSJCppPackageManagerUnitTest> m_vUnitTests;
        std::vector<WSJCppPackageManagerOrigin> m_vOrigins;
        std::vector<std::string> m_sRequiredLibraries;
        std::vector<std::string> m_sRequiredPkgConfig;

        bool m_bHasDocker;
        std::vector<std::string> m_sDockerPackagesBuild;
        std::vector<std::string> m_sDockerPackagesRelease;


        WSJCppYAML m_yamlPackageInfo;
};

#endif // WSJCPP_PACKAGE_MANAGER_H