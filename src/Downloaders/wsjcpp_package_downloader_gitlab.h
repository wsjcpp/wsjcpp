#ifndef WSJCPP_PACKAGE_DOWNLOADER_GITLAB_H
#define WSJCPP_PACKAGE_DOWNLOADER_GITLAB_H

#include <string>
#include "wsjcpp_package_downloader_base.h"

class WsjcppPackageDownloaderGitlab : public WsjcppPackageDownloaderBase {
    public:
        WsjcppPackageDownloaderGitlab();
        virtual bool canDownload(const std::string &sUrl) override;
        virtual bool downloadToCache(const std::string &sPackage, std::string &sError) override;
        
    private:
        std::string TAG;
        std::string m_sName;
};

#endif // WSJCPP_PACKAGE_DOWNLOADER_GITLAB_H