#ifndef WSJCPP_PACKAGE_DOWNLOADERS_H
#define WSJCPP_PACKAGE_DOWNLOADERS_H

#include "wsjcpp_package_downloader_base.h"
#include <vector>

class WsjcppPackageDownloaders {
    public:
        WsjcppPackageDownloaders();
        bool downloadToCache(
            const std::string &sPackage,
            const std::string &sCacheDir,
            WsjcppPackageManagerDependence &dep,
            std::string &sError
        );

    private:
        std::string TAG;
        std::vector<WsjcppPackageDownloaderBase *> m_vDownloaders;
    
};

#endif // WSJCPP_PACKAGE_DOWNLOADERS_H