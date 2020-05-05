
#include "wsjcpp_package_downloader_gitlab.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderGitlab

WsjcppPackageDownloaderGitlab::WsjcppPackageDownloaderGitlab() 
 : WsjcppPackageDownloaderBase("gitlab") {
    TAG = "WsjcppPackageDownloaderGitlab";
    m_sGitlabPrefix = "https://gitlab.com/";
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderGitlab::canDownload(const std::string &sPackage) {
    return sPackage.compare(0, m_sGitlabPrefix.size(), m_sGitlabPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderGitlab::downloadToCache(
    const std::string &sPackage,
    const std::string &sCacheDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    sError = "Not implemented";
    return false;
}

// ---------------------------------------------------------------------
