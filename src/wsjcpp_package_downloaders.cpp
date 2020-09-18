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

WsjcppPackageDownloaders::~WsjcppPackageDownloaders() {
    for (int i = 0; i < m_vDownloaders.size(); i++) {
        delete m_vDownloaders[i];
    }
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaders::downloadToCache(
    const std::string &sPackageUrl,
    const std::string &sCurrentPackageDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    std::string sCacheDir = sCurrentPackageDir + "/.wsjcpp";
    if (!WsjcppCore::dirExists(sCacheDir)) {
        if (!WsjcppCore::makeDir(sCacheDir)) {
            sError = "Could not create dir: '" + sCacheDir + "'";
            return false;
        }
    }
    sCacheDir = sCacheDir + "/cache";
    if (!WsjcppCore::dirExists(sCacheDir)) {
        if (!WsjcppCore::makeDir(sCacheDir)) {
            sError = "Could not create dir: '" + sCacheDir + "'";
            return false;
        }
    }

    sCacheDir = sCacheDir + "/" + WsjcppPackageDownloaderBase::prepareCacheSubFolderName(sPackageUrl);
    
    if (WsjcppCore::dirExists(sCacheDir)) {
        if (!WsjcppCore::recoursiveRemoveDir(sCacheDir)) {
            sError = "Could not recoursive remove dir: '" + sCacheDir + "'";
            return false;
        }
    }

    if (!WsjcppCore::dirExists(sCacheDir)) {
        if (!WsjcppCore::makeDir(sCacheDir)) {
            sError = "Could not create dir: '" + sCacheDir + "'";
            return false;
        }
    }

    // prepare directory with cache
    for (int i = 0; i < m_vDownloaders.size(); i++) {
        WsjcppPackageDownloaderBase *pDownloader = m_vDownloaders[i];
        if (pDownloader->canDownload(sPackageUrl)) {
            bool bResult = pDownloader->downloadToCache(sPackageUrl, sCacheDir, dep, sError);
            if (!bResult) {
                WsjcppCore::recoursiveRemoveDir(sCacheDir);
            }
            return bResult;
        }
    }
 
    sError = "Could not understand where can find package '" + sPackageUrl + "'";
    return false;
}

// ---------------------------------------------------------------------