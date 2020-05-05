#ifndef WSJCPP_PACKAGE_MANAGER_DEPENDENCE_H
#define WSJCPP_PACKAGE_MANAGER_DEPENDENCE_H

#include <string>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------

class WsjcppPackageManagerDependence {
    public:
        WsjcppPackageManagerDependence();
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

        bool fromYAML(WsjcppYamlItem *pYaml);
        WsjcppYamlItem *toYAML();

    private:
        std::string TAG;
        std::string m_sInstallationDir;
        std::string m_sUrl;
        std::string m_sName;
        std::string m_sVersion;
        std::string m_sOrigin;
        WsjcppYamlItem *m_pYamlDependece;
};

// ---------------------------------------------------------------------

#endif // WSJCPP_PACKAGE_MANAGER_DEPENDENCE_H