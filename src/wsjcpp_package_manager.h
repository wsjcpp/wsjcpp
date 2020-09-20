
#ifndef WSJCPP_PACKAGE_MANAGER_H
#define WSJCPP_PACKAGE_MANAGER_H

#include <string>
#include <wsjcpp_yaml.h>
#include "wsjcpp_package_manager_author.h"
#include "wsjcpp_package_manager_safe_scripting_generate.h"
#include "wsjcpp_package_manager_dependence.h"
#include "wsjcpp_package_manager_distribution_file.h"
#include "wsjcpp_package_manager_resource_file.h"
#include "wsjcpp_package_downloaders.h"

// ---------------------------------------------------------------------

class WsjcppPackageManagerOrigin {
    public:
        WsjcppPackageManagerOrigin();
        bool fromYAML(WsjcppYamlItem *pYaml);
        WsjcppYamlItem *toYAML();

        std::string getAddress();
        std::string getType();

        void setAddress(const std::string &sAddress);
        void setType(const std::string &sType);
        
    private:
        std::string TAG;
        std::string m_sAddress;
        std::string m_sType;
        WsjcppYamlItem *m_pYamlOrigin;
};

// ---------------------------------------------------------------------

class WsjcppPackageManagerRepository {
    public:
        WsjcppPackageManagerRepository();
        WsjcppYamlItem *toYAML();
        bool fromYAML(WsjcppYamlItem *pYaml);
        std::string getType();
        std::string getUrl();

    private:
        std::string TAG;
        std::string m_sType;
        std::string m_sUrl;
        WsjcppYamlItem *m_pYamlRepository;
};

// ---------------------------------------------------------------------

class WsjcppPackageManagerUnitTest {
    public:
        WsjcppPackageManagerUnitTest();
        WsjcppYamlItem *toYAML();
        bool fromYAML(WsjcppYamlItem *pYaml);
        std::string getName();
        std::string getDescription();
        bool isEnabled();
        void setName(const std::string &sName);
        void setDescription(const std::string &sDescription);
        void setEnabled(bool bEnabled);

    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sDescription;
        bool m_bEnabled;
        WsjcppYamlItem *m_pYamlUnitTest;
};

// ---------------------------------------------------------------------

class WsjcppPackageManager {
    public:
        WsjcppPackageManager(const std::string &sDir);
        WsjcppPackageManager(const std::string &sDir, const std::string &sParentDir, bool bHolded);
        ~WsjcppPackageManager();
        std::string getDir() const;
        bool isHolded() const;
        bool init();
        bool load();
        bool save();
        void printFiles();
        bool addSourceFile(const std::string &sSourceFile, const std::string &sTargetFile, const std::string &sType);
        bool removeSourceFile(const std::string &sSourceFile);
        bool updateSourceFile(const std::string &sSourceFile, bool bAutoUpdate);
        
        // unit-tests
        bool createUnitTest(const std::string &sUnitTestName, const std::string &sUnitTestDescription);
        bool deleteUnitTest(const std::string &sUnitTestName);
        bool enableUnitTest(const std::string &sUnitTestName, bool bEnable);
        std::vector<WsjcppPackageManagerUnitTest> getListOfUnitTests();

        // safe-scripting-generate
        std::vector<WsjcppPackageManagerSafeScriptingGenerate> getListOfSafeScriptingGenerate();

        bool addOrigin(const std::string &sAddress);
        bool deleteOrigin(const std::string &sAddress);
        bool updateDependencies();
        void verify();
        bool install(const std::string &sPackageUrl, std::string &sError);
        bool checkInstalledPackage(
            const std::string &sPackage,
            std::vector<std::string> &vFilesInstalled,
            std::string &sPackageUrl,
            std::string &sError
        );
        bool reinstall(const std::string &sPackageUrl, std::string &sError);
        bool uninstall(const std::string &sPackageUrl, std::string &sError);
        void printAuthors();
        void printAuthorsTree();
        bool addAuthor(const std::string &sName, const std::string &sEmail);
        bool removeAuthor(const std::string &sAuthor);
        bool addResource(const std::string &sFilepath, const std::string &sPackAs);
        bool removeResource(const std::string &sFilepath);
        bool hasResource(const std::string &sFilepath);
        std::string detectTypeOfResource(const std::string &sFilepath);

        std::vector<WsjcppPackageManagerDistributionFile> getListOfDistributionFiles();
        std::vector<WsjcppPackageManagerDependence> getListOfDependencies();
        std::vector<WsjcppPackageManagerOrigin> getListOfOrigins();
        std::vector<WsjcppPackageManagerAuthor> getListOfAuthors();
        std::vector<std::string> getListOfKeywords();
        std::vector<WsjcppPackageManagerRepository> getListOfRepositories();
        std::vector<WsjcppPackageManagerResourceFile> getListOfResourceFiles();
        
        std::string getName();
        std::string getVersion();
        bool setVersion(const std::string& sVersion);
        std::string getWsjcppVersion();
        std::string getDescription();
        std::string getCMakeCxxStandard();
        std::string getCMakeMinimumRequired();
        std::string getIssues();
        std::string normalizeUnitTestName(const std::string &sUnitTestName, bool bSilent);
        std::string generateFilenameForUnitTest(const std::string &sUnitTestName);

        bool updateAutogeneratedFiles();

        std::string getSampleForBuildSimpleSh();

    private:
        std::string TAG;

        void addDependency(WsjcppPackageManagerDependence &dep);
        void updateDependency(WsjcppPackageManagerDependence &dep);

        std::string generateResourceCppFileBasename(const std::string &sFilepath);
        bool isInstalled(const std::string &sPackage);
        bool installFromCache(const std::string &sPackage, const WsjcppPackageManagerDependence &dep);
        void recursive_printAuthorsTree(std::vector<WsjcppPackageManagerDependence> &vDependencies);
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
        bool readFieldResources();

        void removeDependenciesFilesSafe(const WsjcppPackageManagerDependence &dep);
        bool updateAutogeneratedFiles_CMakeListsTXT();
        bool updateAutogeneratedFiles_Dockerfiles();
        bool updateAutogeneratedFiles_Dockerfile_for_build();
        bool updateAutogeneratedFiles_Dockerfile_for_release();
        bool updateAutogeneratedFiles_Dockerfile_release();
        bool updateAutogeneratedFiles_UnitTests();
        bool updateAutogeneratedFiles_Resource(const WsjcppPackageManagerResourceFile &resFile);
        bool updateAutogeneratedFiles_Resources();
        bool validateVersionFormat(const std::string &sVersion);
        bool append(
            std::vector<WsjcppPackageManagerSafeScriptingGenerate> &vRet,
            const std::string &sSourceFile,
            const std::string &sModuleFile,
            const std::string &sTargetName
        );
        

        std::string m_sDir;
        bool m_bHolded;
        std::string m_sParentDir;
        std::string m_sYamlFilename;
        std::string m_sYamlFullpath;
        std::string m_sWsjcppCurrentVersion;
        std::string m_sWsjcppVersion;
        std::string m_sDirWithSources;
        std::string m_sName;
        std::string m_sIssues;
        std::string m_sVersion;
        std::string m_sDescription;
        std::string m_sCMakeMinimumRequired;
        std::string m_sCMakeCxxStandard;
        
        std::vector<std::string> m_vKeywords;
        std::vector<WsjcppPackageManagerAuthor> m_vAuthors;
        std::vector<WsjcppPackageManagerDependence> m_vDependencies;
        std::vector<WsjcppPackageManagerDistributionFile> m_vDistributionFiles;
        std::vector<WsjcppPackageManagerRepository> m_vRepositories;
        std::vector<WsjcppPackageManagerUnitTest> m_vUnitTests;
        std::vector<WsjcppPackageManagerOrigin> m_vOrigins;
        std::vector<WsjcppPackageManagerResourceFile> m_vResourceFiles;
        std::vector<std::string> m_sRequiredLibraries;
        std::vector<std::string> m_sRequiredPkgConfig;

        bool m_bHasDocker;
        std::vector<std::string> m_sDockerPackagesBuild;
        std::vector<std::string> m_sDockerPackagesRelease;
        std::string m_sDirResources;
        std::string m_sDirnameResources;

        WsjcppYaml m_yamlPackageInfo;
        WsjcppPackageDownloaders *m_pDownloaders;
};

#endif // WSJCPP_PACKAGE_MANAGER_H
