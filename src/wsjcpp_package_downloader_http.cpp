
#include "wsjcpp_package_downloader_http.h"
#include <wsjcpp_core.h>
#include <wsjcpp_hashes.h>
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
    std::vector<std::string> vSubdirs = WsjcppCore::split(sPackage, "/");
    if (vSubdirs[vSubdirs.size()-1] == "") {
        vSubdirs.pop_back();
    }
    vSubdirs.pop_back(); // version
    vSubdirs.pop_back(); // package-name
    std::string sOrigin = WsjcppCore::join(vSubdirs, "/");
    dep.setOrigin(sOrigin);
    return true;
}

// ---------------------------------------------------------------------