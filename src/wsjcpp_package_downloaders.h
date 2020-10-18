#ifndef WSJCPP_PACKAGE_DOWNLOADERS_H
#define WSJCPP_PACKAGE_DOWNLOADERS_H

#include "wsjcpp_package_downloader_base.h"
#include <vector>

class WsjcppPackageDownloaders {
    public:
        WsjcppPackageDownloaders();
        ~WsjcppPackageDownloaders();
        bool downloadToCache(
            const std::string &sPackageUrl,
            const std::string &sCurrentPackageDir,
            WsjcppPackageManagerDependence &dep,
            std::string &sError
        );

    private:
        std::string TAG;
        std::vector<WsjcppPackageDownloaderBase *> m_vDownloaders; 
};

#endif // WSJCPP_PACKAGE_DOWNLOADERS_H