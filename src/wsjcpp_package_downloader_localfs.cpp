
#include "wsjcpp_package_downloader_localfs.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>
#include <sstream>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderLocalFs

WsjcppPackageDownloaderLocalFs::WsjcppPackageDownloaderLocalFs() 
 : WsjcppPackageDownloaderBase("localfs") {
    TAG = "WsjcppPackageDownloaderLocalFs";
    m_sFilePrefix = "file:///";
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderLocalFs::canDownload(const std::string &sPackage) {
    return sPackage.compare(0, m_sFilePrefix.size(), m_sFilePrefix) == 0;
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderLocalFs::downloadToCache(
    const std::string &sPackage,
    const std::string &sCacheDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    sError = "Not implemented";
    return false;
}

// ---------------------------------------------------------------------
