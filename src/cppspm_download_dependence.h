#ifndef CPPSPM_DOWNLOAD_DEPENDENCE_H
#define CPPSPM_DOWNLOAD_DEPENDENCE_H

#include <string>

namespace CppSPM {

class DownloadDependence {
    public:
        static bool downloadZip(const std::string &sUrl, const std::string &zipFile);
};

} // namespace CppSPM

#endif // CPPSPM_DOWNLOAD_DEPENDENCE_H