
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
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderLocalFs::canDownload(const std::string &sPackage) {
    return 
        sPackage.compare(0, m_sFilePrefix.size(), m_sFilePrefix) == 0
        || sPackage.compare(0, m_sFileLinuxPrefix.size(), m_sFileLinuxPrefix) == 0
        || sPackage.compare(0, m_sFileLinuxPrefix2.size(), m_sFileLinuxPrefix2) == 0;
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
    std::cout << "sDirPath = " << sDirPath << std::endl;
    if (!WsjcppCore::dirExists(sDirPath)) {
        sError = "Could not found directory '" + sDirPath + "'";
        return false;
    }

    std::string sWsjCppYml = sCacheDir + "/wsjcpp.yml";
    if (WsjcppCore::fileExists(sWsjCppYml)) {
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

        if (WsjcppCore::fileExists(sWsjCppSourceTo)) {
            WsjcppCore::removeFile(sWsjCppSourceTo);
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
