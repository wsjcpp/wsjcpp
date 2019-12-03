#include "wsjcpp_packager_download_dependence.h"
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
// #include <curl.h> 

#include <curl/curl.h>
// #include <curl/types.h> 
// #include <curl/easy.h> 
#include <string> 
#include <iostream> 
#include <wsjcpp_core.h>
#include "zip.h"

namespace CppSPM {

    size_t downloadZipWriteDataFile(void *ptr, size_t size, size_t nmemb, FILE *stream) { 
        size_t written = fwrite(ptr, size, nmemb, stream); 
        return written; 
    }

    // ---------------------------------------------------------------------
    
    bool DownloadDependence::unzipFile(const std::string &zipFile, const std::string &targetFolder) {
        //Open the ZIP archive
        int err = 0;
        zip *z = zip_open(zipFile.c_str(), 0, &err);
        if (!z) {
		    fprintf(stderr,"Error: can't open file %s\n",zipFile.c_str());
		    return -1;
	    };

        int files_total = zip_get_num_files(z); // количество файлов в архиве
	    printf("Files in ZIP: %d\n", files_total);
        struct zip_stat file_info; // информация о файле
        struct tm file_time;

        for (int i = 0; i < files_total; i++) {
            // получаем информацию о файле с номером i в структуру file_info
            zip_stat_index(z, i, 0, &file_info);
            printf("index=%d ",file_info.index); // номер файла
            printf("name=\"%s\" ",file_info.name); // имя файла
            printf("size=%u ",file_info.size); // размер файла
            /*
            localtime_r(&file_info.mtime, &file_time); // дата модификации файла
            printf("date=\"%02d-%02d-%04d %02d:%02d\"",
                file_time.tm_mday,file_time.tm_mon+1,
                file_time.tm_year+1900, file_time.tm_hour,
                file_time.tm_min);
            */
            printf("\n");
        };	

        //Search for the file of given name
        /* const char *name = "file.txt";
        struct zip_stat st;
        zip_stat_init(&st);
        zip_stat(z, name, 0, &st);

        //Alloc memory for its uncompressed contents
        char *contents = new char[st.size];

        //Read the compressed file
        zip_file *f = zip_fopen(z, name, 0);
        zip_fread(f, contents, st.size);
        zip_fclose(f);
        */
        //And close the archive
        zip_close(z);

        //Do something with the contents
        //delete allocated memory
        // delete[] contents;
        return true;
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
    std::string targetFolder = zipFile + "_unzipped";
    if (!DownloadDependence::unzipFile(zipFile, targetFolder)) {
        return false;
    }

    // std::vector<std::string> dirs = Fallen::listOfDirs()
    return false;
};

} // namespace CppSPM
