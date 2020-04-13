#ifndef WSJCPP_PACKAGE_MANAGER_RESOURCE_FILE_H
#define WSJCPP_PACKAGE_MANAGER_RESOURCE_FILE_H

#include <string>
#include <wsjcpp_yaml.h>


// ---------------------------------------------------------------------

class WsjcppPackageManagerResourceFile {
    public:
        WsjcppPackageManagerResourceFile();
        bool fromYAML(WsjcppYamlItem *pYamlResourceFile, bool bHolded);
        WsjcppYamlItem *toYAML();

        std::string getFilepath() const;
        long getFilesize() const;
        std::string getSha1() const;
        std::string getPackAs() const;
        long getModified() const;

        void setFilepath(const std::string &sFilepath);
        void setFilesize(long nFilesize);
        void setSha1(const std::string &sSha1);
        void setPackAs(const std::string &sPackAs);
        void setModified(long nModified);

    private:
        std::string TAG;
        bool m_bHolded;
        std::string m_sFilepath;
        long m_nFilesize;
        std::string m_sSha1;
        std::string m_sPackAs;
        long m_nModified;
        WsjcppYamlItem *m_pYamlResourceFile;
};

#endif // WSJCPP_PACKAGE_MANAGER_RESOURCE_FILE_H