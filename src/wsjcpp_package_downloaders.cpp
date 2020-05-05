#include "wsjcpp_package_downloaders.h"
#include "wsjcpp_package_downloader_bitbucket.h"
#include "wsjcpp_package_downloader_github.h"
#include "wsjcpp_package_downloader_gitlab.h"
#include "wsjcpp_package_downloader_localfs.h"
#include "wsjcpp_package_downloader_http.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaders

WsjcppPackageDownloaders::WsjcppPackageDownloaders() {
    TAG = "WsjcppPackageDownloaders";
    m_vDownloaders.push_back(new WsjcppPackageDownloaderLocalFs());
    m_vDownloaders.push_back(new WsjcppPackageDownloaderBitbucket());
    m_vDownloaders.push_back(new WsjcppPackageDownloaderGithub());
    m_vDownloaders.push_back(new WsjcppPackageDownloaderGitlab());
    m_vDownloaders.push_back(new WsjcppPackageDownloaderHttp());
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaders::downloadToCache(
    const std::string &sPackage,
    const std::string &sCacheDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    // TODO cleanup folder before download
    for (int i = 0; m_vDownloaders.size(); i++) {
        WsjcppPackageDownloaderBase *pDownloader = m_vDownloaders[i];
        if (pDownloader->canDownload(sPackage)) {
            return pDownloader->downloadToCache(sPackage, sCacheDir, dep, sError);
        }
    }
    return false;
}

// ---------------------------------------------------------------------