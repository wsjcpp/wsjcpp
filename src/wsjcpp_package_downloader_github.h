#ifndef WSJCPP_PACKAGE_DOWNLOADER_GITHUB_H
#define WSJCPP_PACKAGE_DOWNLOADER_GITHUB_H

#include <string>
#include "wsjcpp_package_downloader_base.h"

class WsjcppPackageDownloaderGithub : public WsjcppPackageDownloaderBase {
    public:
        WsjcppPackageDownloaderGithub();
        virtual bool canDownload(const std::string &sPackage) override;
        virtual bool downloadToCache(
            const std::string &sPackage,
            const std::string &sCacheDir,
            WsjcppPackageManagerDependence &dep,
            std::string &sError
        ) override;
        
    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sGithubPrefix;
};

#endif // WSJCPP_PACKAGE_DOWNLOADER_GITHUB_H