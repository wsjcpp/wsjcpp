#include "wsjcpp_package_downloader_bitbucket.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>
#include <sstream>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderBitbucket

WsjcppPackageDownloaderBitbucket::WsjcppPackageDownloaderBitbucket() 
 : WsjcppPackageDownloaderBase("bitbucket") {
    TAG = "WsjcppPackageDownloaderBitbucket";
    m_sBitbucketPrefix = "https://bitbucket.org/";
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderBitbucket::canDownload(const std::string &sPackage) {
    return sPackage.compare(0, m_sBitbucketPrefix.size(), m_sBitbucketPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderBitbucket::downloadToCache(
    const std::string &sPackage,
    const std::string &sCacheDir,
    WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    std::cout << "Download package from " << m_sBitbucketPrefix << " ..." << std::endl;

    std::string sPackageGithubPath = sPackage.substr(m_sBitbucketPrefix.size());
    std::istringstream f(sPackageGithubPath);
    std::string packageName = "";
    std::string s;
    if (getline(f, s, ':')) {
        packageName = s;
    }
    std::string packageVersion = sPackageGithubPath.substr(packageName.size()+1);
    std::string sWsjcppBaseUrl = "https://bitbucket.org/" + packageName + "/raw/" + packageVersion + "/";
    std::string sDownloadedWsjCppYml = sCacheDir + "/wsjcpp.hold.yml";


    if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sWsjcppBaseUrl + "/wsjcpp.yml", sDownloadedWsjCppYml)) {
        sError = "Could not download " + sWsjcppBaseUrl;
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

        std::cout << "Downloading '" << sDownloadedWsjCppSourceFrom << "' -> '" << sDownloadedWsjCppSourceTo << "' ... " << std::endl;
        if (!WsjcppPackageDownloaderBase::downloadFileOverHttps(sDownloadedWsjCppSourceFrom, sDownloadedWsjCppSourceTo)) {
            WsjcppLog::err(TAG, "Could not download " + sDownloadedWsjCppSourceFrom);
            // TODO remove from cache
            return false;
        }
        std::cout << "OK" << std::endl;
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
    dep.setOrigin("https://bitbucket.org/");
    return true;
}

// ---------------------------------------------------------------------
