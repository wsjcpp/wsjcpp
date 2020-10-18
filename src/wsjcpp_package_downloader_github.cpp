
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
    std::cout << "Try download package to " << sCacheDir << std::endl;
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

    std::cout << "Downloading " << sWsjcppBaseUrl << "/wsjcpp.yml" << std::endl;
    if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sWsjcppBaseUrl + "/wsjcpp.yml", sCacheDir + "/wsjcpp.yml")) {
        WsjcppLog::err(TAG, "Could not download " + sWsjcppBaseUrl);
        return false;
    }

    WsjcppPackageManager pkg(sCacheDir);
    if (!pkg.load()) {
        sError = "Could not load " + sCacheDir;
        return false;
    }

    // downlod sources
    std::vector<WsjcppPackageManagerDistributionFile> vSources = pkg.getListOfDistributionFiles();
    for (int i = 0; i < vSources.size(); i++) {
        WsjcppPackageManagerDistributionFile src = vSources[i];
        if (!WsjcppPackageDownloaderBase::prepareCacheSubdirForFile(sCacheDir, src.getSourceFile(), sError)) {
            return false;
        }
        

        std::string sDownloadedWsjCppSourceFrom = sWsjcppBaseUrl + "/" + src.getSourceFile();
        std::string sDownloadedWsjCppSourceTo = sCacheDir + "/" + src.getSourceFile();

        std::cout << "Downloading " << sDownloadedWsjCppSourceFrom << std::endl;

        // WsjcppLog::info(TAG, "\nDownloading " + sDownloadedWsjCppSourceFrom + " \n\t-> \n\t" + sDownloadedWsjCppSourceTo + "\n\t[sha1:" + src.getSha1() + "]");
        if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sDownloadedWsjCppSourceFrom, sDownloadedWsjCppSourceTo)) {
            WsjcppLog::err(TAG, "Could not download " + sDownloadedWsjCppSourceFrom);
            return false;
        }
        if (!pkg.updateSourceFile(src.getSourceFile(), false)) {
            sError = "Could not update file '" + sDownloadedWsjCppSourceFrom + "'";
            return false;
        }
    }
    pkg.save();

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
