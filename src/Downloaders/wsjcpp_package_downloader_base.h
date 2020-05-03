#ifndef WSJCPP_PACKAGE_DOWNLOADER_BASE_H
#define WSJCPP_PACKAGE_DOWNLOADER_BASE_H

#include <string>

class WsjcppPackageDownloaderBase {
    public:
        WsjcppPackageDownloaderBase(const std::string &sName);
        virtual bool canDownload(const std::string &sUrl) = 0;
        virtual bool downloadToCache(const std::string &sPackage, std::string &sError) = 0;
        
    private:
        std::string TAG;
        std::string m_sName;
};

#endif // WSJCPP_PACKAGE_DOWNLOADER_BASE_H