#include "cppspm_download_dependence.h"
#include <iostream>
#include <stdio.h> 
// #include <curl.h> 
// #include <types.h> 
// #include <easy.h> 
#include <string> 
#include <iostream> 

namespace CppSPM {

bool DownloadDependence::downloadZip(const std::string &sUrl, const std::string &zipFile) {
    std::cout << "url: " << sUrl << std::endl;
    std::cout << "zip: " << zipFile << std::endl;


    
    // example code for download zip file
    /* using namespace std; 

    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE 
    *stream) { 
    size_t written = fwrite(ptr, size, nmemb, stream); 
    return written; 
    } 

    int main(void) { 
    CURL *curl; 
    FILE *fp; 
    CURLcode res; 
    char *url = "http://test.com/update/testt.zip"; 
    char outfilename[FILENAME_MAX] = "test.zip"; 
    curl = curl_easy_init(); 
    if (curl) { 
    fp = fopen(outfilename,"wb"); 
    if (fp !=NULL) 
    { 
    cout << "file opened\n"; 
    } 
    curl_easy_setopt(curl, CURLOPT_URL, 
    "http://test.com/update/testt.zip"); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); 
    res = curl_easy_perform(curl); 
    // always cleanup
    curl_easy_cleanup(curl); 
    fclose(fp); 
        system("PAUSE"); //so i can see output 
    } 
    return 0; 
    } */

    return false;
};

} // namespace CppSPM
