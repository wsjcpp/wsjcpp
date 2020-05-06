
#include "wsjcpp_package_downloader_http.h"
#include <wsjcpp_core.h>
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

    std::string sDownloadedWsjCppYml = sCacheDir + "/wsjcpp.hold.yml";
    if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sWsjcppBaseUrl + "/wsjcpp.yml", sDownloadedWsjCppYml)) {
        sError = "Could not download " + sWsjcppBaseUrl;
        // TODO remove from cache
        return false;
    }

    WsjcppPackageManager pkg(sCacheDir, sCacheDir, true);
    if (!pkg.load()) {
        sError = "Could not load " + sCacheDir;
        return false;
    }

    // sources
    std::vector<WsjcppPackageManagerDistributionFile> vSources = pkg.getListOfDistributionFiles();
    for (int i = 0; i < vSources.size(); i++) {
        WsjcppPackageManagerDistributionFile src = vSources[i];
        std::string sDownloadedWsjCppSourceFrom = sWsjcppBaseUrl + "/" + src.getSourceFile();
        std::string sDownloadedWsjCppSourceTo = sCacheDir + "/" + src.getTargetFile();

        WsjcppLog::info(TAG, "\n\t" + sDownloadedWsjCppSourceFrom + " \n\t-> \n\t" + sDownloadedWsjCppSourceTo + "\n\t[sha1:" + src.getSha1() + "]");
        if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sDownloadedWsjCppSourceFrom, sDownloadedWsjCppSourceTo)) {
            sError = "Could not download " + sDownloadedWsjCppSourceFrom;
            // TODO remove from cache
            return false;
        }
        std::string sContent = "";
        if (!WsjcppCore::readTextFile(sDownloadedWsjCppSourceTo, sContent)) {
            sError = "Could not read file " + sDownloadedWsjCppSourceTo;
            return false;
        }
        // TODO set calculated sha1
        // std::string sSha1 = WsjcppHashes::sha1_calc_hex(sContent);
        // src.setSha1(sSha1);
    }

    std::string sInstallationDir = "./src.wsjcpp/" + WsjcppPackageDownloaderBase::prepareCacheSubFolderName(pkg.getName());

    // WsjcppPackageManagerDependence dep;
    dep.setName(pkg.getName());
    dep.setVersion(pkg.getVersion());
    dep.setUrl(sPackage);
    dep.setInstallationDir(sInstallationDir);
    dep.setOrigin("https://github.com/"); // TODO remove "package-name/version"
    return true;
}

// ---------------------------------------------------------------------