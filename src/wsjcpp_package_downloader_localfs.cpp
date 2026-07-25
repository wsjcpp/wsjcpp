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

#include "wsjcpp_package_downloader_localfs.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>
#include <sstream>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderLocalFs

WsjcppPackageDownloaderLocalFs::WsjcppPackageDownloaderLocalFs() 
 : WsjcppPackageDownloaderBase("localfs") {
    TAG = "WsjcppPackageDownloaderLocalFs";
    m_sFilePrefix = "file://";
    m_sFileLinuxPrefix = "/";
    m_sFileLinuxPrefix2 = "../";
    m_sFileLinuxPrefix3 = "./";
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderLocalFs::canDownload(const std::string &sPackage) {
    return 
        sPackage.compare(0, m_sFilePrefix.size(), m_sFilePrefix) == 0
        || sPackage.compare(0, m_sFileLinuxPrefix.size(), m_sFileLinuxPrefix) == 0
        || sPackage.compare(0, m_sFileLinuxPrefix2.size(), m_sFileLinuxPrefix2) == 0
        || sPackage.compare(0, m_sFileLinuxPrefix3.size(), m_sFileLinuxPrefix3) == 0
    ;
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderLocalFs::downloadToCache(
    const std::string &sPackage,
    const std::string &sCacheDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    std::string sDirPath = sPackage;
    std::cout << "sDirPath = " << sDirPath << std::endl;
    if (sDirPath.compare(0, m_sFilePrefix.size(), m_sFilePrefix) == 0) {
        int nPrSize = m_sFilePrefix.size();
        sDirPath = sDirPath.substr(nPrSize, sDirPath.size() - nPrSize);
    }
    // std::cout << "sDirPath = " << sDirPath << std::endl;
    if (!wsjcpp::dir_exists(sDirPath)) {
        sError = "Could not found directory '" + sDirPath + "'";
        return false;
    }

    std::string sWsjCppYml = sCacheDir + "/wsjcpp.yml";
    if (wsjcpp::file_exists(sWsjCppYml)) {
        WsjcppCore::removeFile(sWsjCppYml);
    }
    if (!WsjcppCore::copyFile(sDirPath + "/wsjcpp.yml", sWsjCppYml)) {
        sError = "Could not copy file '" + sDirPath + "/wsjcpp.yml' to '" + sWsjCppYml + "'";
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

        std::string sWsjCppSourceFrom = sDirPath + "/" + src.getSourceFile();
        std::string sWsjCppSourceTo = sCacheDir + "/" + src.getSourceFile();

        std::cout
            << "    Copy file from '" << sWsjCppSourceFrom << "'" << " to '" << sWsjCppSourceTo << "'."
            << std::endl;

        if (wsjcpp::file_exists(sWsjCppSourceTo)) {
            WsjcppCore::removeFile(sWsjCppSourceTo);
        }

        std::string sDir = sWsjCppSourceTo.substr(0, sWsjCppSourceTo.length() - wsjcpp::extract_filename(sWsjCppSourceTo).length());
        std::cout << "sDir = " << sDir << std::endl;
        if (!wsjcpp::dir_exists(sDir)) {
            if (!WsjcppCore::makeDir(sDir)) {
                sError = "Could not make directory " + sDir;
                return false;
            }
        }

        if (!WsjcppCore::copyFile(sWsjCppSourceFrom, sWsjCppSourceTo)) {
            sError = "Could not copy " + sWsjCppSourceFrom;
            return false;
        } else {
            std::cout
                << "    Completed." << std::endl;
        }

        if (!pkg.updateSourceFile(src.getSourceFile(), false)) {
            sError = "Could not download " + sWsjCppSourceFrom;
            return false;
        }
    }
    pkg.save();

    std::string sInstallationDir = "./src.wsjcpp/" + WsjcppPackageDownloaderBase::prepareCacheSubFolderName(pkg.getName());

    dep.setName(pkg.getName());
    dep.setVersion(pkg.getVersion());
    dep.setUrl(sPackage);
    dep.setInstallationDir(sInstallationDir);
    dep.setOrigin("localfs");
    return true;
}

// ---------------------------------------------------------------------
