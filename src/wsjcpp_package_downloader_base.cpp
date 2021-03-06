
#include "wsjcpp_package_downloader_base.h"
#include <wsjcpp_core.h>
#include <curl/curl.h>

// ---------------------------------------------------------------------
// WsjcppPackageDownloaderBase

WsjcppPackageDownloaderBase::WsjcppPackageDownloaderBase(const std::string &sName) {
    TAG = "WsjcppPackageDownloaderBase";
    m_sName = sName;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageDownloaderBase::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageDownloaderBase::prepareCacheSubFolderName(const std::string &sPackage) {
    std::string ret = sPackage;
    std::string illegalChars = "\\/:?\"<>|.-";
    std::string::iterator it;
    for (it = ret.begin(); it < ret.end() ; ++it) {
        if (illegalChars.find(*it) != std::string::npos) {
            *it = '_';
        }
    }
    return ret;
}

// ---------------------------------------------------------------------

size_t CurlWrite_CallbackFunc_DataToFile(void *ptr, size_t size, size_t nmemb, FILE *stream) { 
    size_t written = fwrite(ptr, size, nmemb, stream); 
    return written; 
}

bool WsjcppPackageDownloaderBase::downloadFileOverHttps(const std::string &sUrl, const std::string &sPath) {
    std::string TAG = "downloadFileOverHttps";
    // WsjcppLog::info(TAG, "sUrl: '" + sUrl + "'");
    // WsjcppLog::info(TAG, "sPath: '" + sPath + "'");
    std::string sUserAgent = "wsjcpp/" + std::string(WSJCPP_APP_VERSION);
    CURL *curl;
    FILE *fp = fopen(sPath.c_str(),"wb"); 
    if (fp == NULL) { 
        WsjcppLog::err(TAG, "Could not open file for write '" + sPath + "'"); 
        return false;
    }

    CURLcode res;
    long response_code = 0;
    curl = curl_easy_init(); 
    if (curl) { 
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https
        curl_easy_setopt(curl, CURLOPT_URL, sUrl.c_str()); 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_DataToFile); 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, sUserAgent.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl); 
        if (res != CURLE_OK) {
            WsjcppLog::err(TAG, "Curl failed, reason  " + std::string(curl_easy_strerror(res))); 
            // TODO remove file
        } else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code != 200) {
                WsjcppLog::info(TAG, "end " + std::to_string(response_code));
                // TODO remove file
            }
        }

        // always cleanup
        curl_easy_cleanup(curl); 
    }

    fclose(fp);
    return res == CURLE_OK && response_code == 200;
}

// ---------------------------------------------------------------------

bool WsjcppPackageDownloaderBase::prepareCacheSubdirForFile(const std::string &sCacheDir, const std::string &sFilePath, std::string &sError) {
    std::vector<std::string> vSubdirs = WsjcppCore::split(sFilePath, "/");
    vSubdirs.pop_back(); // remove filename
    std::string sPath = WsjcppCore::doNormalizePath(sCacheDir);
    for (int x = 0; x < vSubdirs.size(); x++) {
        if (vSubdirs[x] == ".") {
            continue; // skip
        }
        if (vSubdirs[x] == "..") {
            sError = "Source file path must not contains '..' in path";
            return false;
        }
        sPath = WsjcppCore::doNormalizePath(sPath + "/" + vSubdirs[x]);
        if (!WsjcppCore::dirExists(sPath)) {
            if (!WsjcppCore::makeDir(sPath)) {
                sError = "Could not create dir: '" + sPath + "'";
                return false;
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------