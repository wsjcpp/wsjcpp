#ifndef WSJCPP_PACKAGE_MANAGER_DISTRIBUTION_FILE_H
#define WSJCPP_PACKAGE_MANAGER_DISTRIBUTION_FILE_H

#include <string>
#include <wsjcpp_yaml.h>


// ---------------------------------------------------------------------

class WSJCppPackageManagerDistributionFile {
    public:
        WSJCppPackageManagerDistributionFile();
        bool fromYAML(WSJCppYAMLItem *pYamlDistributionFile, bool bHolded);
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
        bool m_bHolded;
};

#endif // WSJCPP_PACKAGE_MANAGER_DISTRIBUTION_FILE_H