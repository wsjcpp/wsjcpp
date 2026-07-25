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

#include "wsjcpp_package_downloader_http.h"
#include <wsjcpp_core.h>
#include "s5k/utils/s5k_helpers.h"
#include <wsjcpp_package_manager.h>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderHttp

WsjcppPackageDownloaderHttp::WsjcppPackageDownloaderHttp()
 : WsjcppPackageDownloaderBase("http") {
    TAG = "WsjcppPackageDownloaderHttp";
    m_sHttpPrefix = "http://"; // from some http://
    m_sHttpsPrefix = "https://";
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderHttp::canDownload(const std::string &sPackage) {
    return
        sPackage.compare(0, m_sHttpPrefix.size(), m_sHttpPrefix) == 0
        || sPackage.compare(0, m_sHttpsPrefix.size(), m_sHttpsPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderHttp::downloadToCache(
    const std::string &sPackage,
    const std::string &sCacheDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    std::cout << "Download package from " << sPackage << " ..." << std::endl;
   
    std::string sWsjcppBaseUrl = sPackage;

    std::string sDownloadedWsjCppYml2 = sCacheDir + "/wsjcpp.yml";
    if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sWsjcppBaseUrl + "/wsjcpp.yml", sDownloadedWsjCppYml2)) {
        sError = "Could not download " + sWsjcppBaseUrl;
        return false;
    }

    WsjcppPackageManager pkg(sCacheDir);
    if (!pkg.load()) {
        sError = "Could not load " + sCacheDir;
        return false;
    }

    // sources
    std::vector<WsjcppPackageManagerDistributionFile> vSources = pkg.getListOfDistributionFiles();
    for (int i = 0; i < vSources.size(); i++) {
        WsjcppPackageManagerDistributionFile src = vSources[i];
        std::cout << "  - " << src.getSourceFile() << ": " << std::endl;
        if (!WsjcppPackageDownloaderBase::prepareCacheSubdirForFile(sCacheDir, src.getSourceFile(), sError)) {
            return false;
        }

        std::string sDownloadedWsjCppSourceFrom = sWsjcppBaseUrl + "/" + src.getSourceFile();
        std::string sDownloadedWsjCppSourceTo = sCacheDir + "/" + src.getSourceFile();
        
        std::cout
            << "    Downloading file from '" << sDownloadedWsjCppSourceFrom << "'" << " to '" << sDownloadedWsjCppSourceTo << "'."
            << std::endl;

        if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sDownloadedWsjCppSourceFrom, sDownloadedWsjCppSourceTo)) {
            sError = "Could not download " + sDownloadedWsjCppSourceFrom;
            return false;
        } else {
            std::cout  
                << "    Completed." << std::endl;
        }

        std::string sContent = "";
        if (!WsjcppCore::readTextFile(sDownloadedWsjCppSourceTo, sContent)) {
            sError = "Could not read file " + sDownloadedWsjCppSourceTo;
            return false;
        }
        if (!pkg.updateSourceFile(src.getSourceFile(), false)) {
            sError = "Could not download " + sDownloadedWsjCppSourceFrom;
            return false;
        }
    }
    pkg.save();

    std::string sInstallationDir = "./src.wsjcpp/" + WsjcppPackageDownloaderBase::prepareCacheSubFolderName(pkg.getName());

    dep.setName(pkg.getName());
    dep.setVersion(pkg.getVersion());
    dep.setUrl(sPackage);
    dep.setInstallationDir(sInstallationDir);

    // remove package/version from url
    std::vector<std::string> vSubdirs = wsjcpp::split(sPackage, "/");
    if (vSubdirs[vSubdirs.size()-1] == "") {
        vSubdirs.pop_back();
    }
    vSubdirs.pop_back(); // version
    vSubdirs.pop_back(); // package-name
    std::string sOrigin = wsjcpp::join(vSubdirs, "/");
    dep.setOrigin(sOrigin);
    return true;
}

// ---------------------------------------------------------------------