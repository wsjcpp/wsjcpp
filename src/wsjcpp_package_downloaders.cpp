/*
 * MIT License
 *
 * Copyright (c) 2019-2026 Evgenii Sopov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

// original source-code: https://github.com/wsjcpp/wsjcpp

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
    if (!wsjcpp::dir_exists(sCacheDir)) {
        if (!WsjcppCore::makeDir(sCacheDir)) {
            sError = "Could not create dir: '" + sCacheDir + "'";
            return false;
        }
    }
    sCacheDir = sCacheDir + "/cache";
    if (!wsjcpp::dir_exists(sCacheDir)) {
        if (!WsjcppCore::makeDir(sCacheDir)) {
            sError = "Could not create dir: '" + sCacheDir + "'";
            return false;
        }
    }

    sCacheDir = sCacheDir + "/" + WsjcppPackageDownloaderBase::prepareCacheSubFolderName(sPackageUrl);

    if (wsjcpp::dir_exists(sCacheDir)) {
        if (!wsjcpp::recursive_remove_dir(sCacheDir, sError)) {
            sError = "Could not recursive remove dir: '" + sCacheDir + "'";
            return false;
        }
    }

    if (!wsjcpp::dir_exists(sCacheDir)) {
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
                wsjcpp::recursive_remove_dir(sCacheDir, sError);
            }
            return bResult;
        }
    }
 
    sError = "Could not understand where can find package '" + sPackageUrl + "'";
    return false;
}

// ---------------------------------------------------------------------