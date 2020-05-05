#include "wsjcpp_package_downloader_bitbucket.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>
#include <sstream>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderBitbucket

WsjcppPackageDownloaderBitbucket::WsjcppPackageDownloaderBitbucket() 
 : WsjcppPackageDownloaderBase("localfs") {
    TAG = "WsjcppPackageDownloaderBitbucket";
    m_sBitbucketPrefix = "https://bitbucket.com/";
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderBitbucket::canDownload(const std::string &sPackage) {
    return sPackage.compare(0, m_sBitbucketPrefix.size(), m_sBitbucketPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderBitbucket::downloadToCache(
    const std::string &sPackage,
    const std::string &sCacheDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    sError = "Not implemented";
    return false;
}

// ---------------------------------------------------------------------
