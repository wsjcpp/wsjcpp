#ifndef WSJCPP_PACKAGE_DOWNLOADER_BASE_H
#define WSJCPP_PACKAGE_DOWNLOADER_BASE_H

#include <string>
#include <wsjcpp_package_manager_dependence.h>

class WsjcppPackageDownloaderBase {
    public:
        WsjcppPackageDownloaderBase(const std::string &sName);
        virtual bool canDownload(const std::string &sPackage) = 0;
        virtual bool downloadToCache(
            const std::string &sPackage,
            const std::string &sCacheDir,
            WsjcppPackageManagerDependence &dep,
            std::string &sError
        ) = 0;
        static std::string prepareCacheSubFolderName(const std::string &sPackage);
        static bool downloadFileOverHttps(const std::string &sUrl, const std::string &sPath);

    protected:
        std::string TAG;
        

    private:
        std::string m_sName;
};

#endif // WSJCPP_PACKAGE_DOWNLOADER_BASE_H