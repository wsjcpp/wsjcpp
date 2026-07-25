/*
 * MIT License
 *
 * Copyright (c) 2019-2026 Evgenii Sopov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

// original source-code: https://github.com/wsjcpp/wsjcpp

#ifndef WSJCPP_PACKAGE_DOWNLOADER_BASE_H
#define WSJCPP_PACKAGE_DOWNLOADER_BASE_H

#include <string>
#include <wsjcpp_package_manager_dependence.h>

class WsjcppPackageDownloaderBase {
    public:
        WsjcppPackageDownloaderBase(const std::string &sName);
        virtual ~WsjcppPackageDownloaderBase() {};
        std::string getName();
        virtual bool canDownload(const std::string &sPackage) = 0;
        virtual bool downloadToCache(
            const std::string &sPackage,
            const std::string &sCacheDir,
            WsjcppPackageManagerDependence &dep,
            std::string &sError
        ) = 0;
        static std::string prepareCacheSubFolderName(const std::string &sPackage);
        static bool downloadFileOverHttps(const std::string &sUrl, const std::string &sPath);
        // TODO move to core like a 'mkdir -p'
        static bool prepareCacheSubdirForFile(const std::string &sCacheDir, const std::string &sFilePath, std::string &sError);
    protected:
        std::string TAG;
        

    private:
        std::string m_sName;
};

#endif // WSJCPP_PACKAGE_DOWNLOADER_BASE_H