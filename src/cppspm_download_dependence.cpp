#include "cppspm_download_dependence.h"
#include <iostream>
#include <stdio.h> 
// #include <curl.h> 

#include <curl/curl.h>
// #include <curl/types.h> 
// #include <curl/easy.h> 
#include <string> 
#include <iostream> 

namespace CppSPM {

size_t downloadZipWriteDataFile(void *ptr, size_t size, size_t nmemb, FILE *stream) { 
    size_t written = fwrite(ptr, size, nmemb, stream); 
    return written; 
}

// ---------------------------------------------------------------------

bool DownloadDependence::downloadZipFromGithub(const std::string &sUrl, const std::string &zipFile) {
    std::cout << "url: " << sUrl << std::endl;
    std::cout << "zip: " << zipFile << std::endl;
    
    CURL *curl;
    FILE *fp; 
    CURLcode res; 
    // char outfilename[FILENAME_MAX] = zipFile.c_str(); 
    curl = curl_easy_init(); 
    if (curl) { 
    fp = fopen(zipFile.c_str(),"wb"); 
    if (fp != NULL) { 
        std::cout << "file opened\n"; 
    } 
    curl_easy_setopt(curl, CURLOPT_URL, sUrl.c_str()); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadZipWriteDataFile); 
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.47.0");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl); 
    // always cleanup
    curl_easy_cleanup(curl); 
    fclose(fp); 
        system("PAUSE"); //so i can see output 
    } 
    return false;
};

} // namespace CppSPM
