
#include "wsjcpp_package_downloader_github.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>
#include <sstream>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderGithub

WsjcppPackageDownloaderGithub::WsjcppPackageDownloaderGithub() 
 : WsjcppPackageDownloaderBase("github") {
    TAG = "WsjcppPackageDownloaderGithub";
    m_sGithubPrefix = "https://github.com/";
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderGithub::canDownload(const std::string &sPackage) {
    return sPackage.compare(0, m_sGithubPrefix.size(), m_sGithubPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderGithub::downloadToCache(
    const std::string &sPackage,
    const std::string &sCacheDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    std::cout << "Download package from https://github.com/ ..." << std::endl;

    std::string sPackageGithubPath = sPackage.substr(m_sGithubPrefix.size());
    // std::cout << "sPackageGithubPath: " << sPackageGithubPath << std::endl;
    std::istringstream f(sPackageGithubPath);
    std::string packageName = "";
    std::string s;
    if (getline(f, s, ':')) {
        packageName = s;
    }
    std::string packageVersion = sPackageGithubPath.substr(packageName.size()+1);
    std::string sWsjcppBaseUrl = "https://raw.githubusercontent.com/" + packageName + "/" + packageVersion + "/";

    std::string sWsjcppUrl = sWsjcppBaseUrl + "/wsjcpp.yml";

    std::string sDownloadedWsjCppYml = sCacheDir + "/wsjcpp.hold.yml";

    if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sWsjcppBaseUrl + "/wsjcpp.yml", sDownloadedWsjCppYml)) {
        WsjcppLog::err(TAG, "Could not download " + sWsjcppBaseUrl);
        // TODO remove from cache
        return false;
    }

    WsjcppPackageManager pkg(sCacheDir, sCacheDir, true);
    if (!pkg.load()) {
        WsjcppLog::err(TAG, "Could not load " + sCacheDir);
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
            WsjcppLog::err(TAG, "Could not download " + sDownloadedWsjCppSourceFrom);
            // TODO remove from cache
            return false;
        }
        // std::string sContent = "";
        // if (!WsjcppCore::readTextFile(sDownloadedWsjCppSourceTo, sContent)) {
        //   WsjcppLog::err(TAG, "Could not read file " + sDownloadedWsjCppSourceTo);
        //    return false;
        // }
        // calculate sha1
        // std::string sSha1 = WsjcppHashes::sha1_calc_hex(sContent);
        // if (sSha1 != src.getSha1()) {
        //    WsjcppLog::warn(TAG, "Expected sha1 '" + sSha1 + "', but got '" + src.getSha1() + "'");
        // }
    }

    std::string sInstallationDir = "./src.wsjcpp/" + WsjcppPackageDownloaderBase::prepareCacheSubFolderName(pkg.getName());

    // WsjcppPackageManagerDependence dep;
    dep.setName(pkg.getName());
    dep.setVersion(pkg.getVersion());
    dep.setUrl(sPackage);
    dep.setInstallationDir(sInstallationDir);
    dep.setOrigin("https://github.com/");
    return true;
}

// ---------------------------------------------------------------------
