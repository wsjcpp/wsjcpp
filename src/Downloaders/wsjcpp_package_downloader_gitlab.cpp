
#include "wsjcpp_package_downloader_gitlab.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderGitlab

WsjcppPackageDownloaderGitlab::WsjcppPackageDownloaderGitlab() 
 : WsjcppPackageDownloaderBase("gitlab") {
    TAG = "WsjcppPackageDownloaderGitlab";
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderGitlab::canDownload(const std::string &sUrl) {

}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderGitlab::downloadToCache(const std::string &sPackage, std::string &sError) {

}

// ---------------------------------------------------------------------
