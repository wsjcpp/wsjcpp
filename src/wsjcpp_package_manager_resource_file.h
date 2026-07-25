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

#ifndef WSJCPP_PACKAGE_MANAGER_RESOURCE_FILE_H
#define WSJCPP_PACKAGE_MANAGER_RESOURCE_FILE_H

#include <string>
#include <wsjcpp_yaml.h>

class WsjcppPackageManagerResourceFile {
    public:
        WsjcppPackageManagerResourceFile();
        bool fromYAML(WsjcppYamlNode *pYamlResourceFile, bool bHolded);
        WsjcppYamlNode *toYAML();

        std::string getFilepath() const;
        long getFilesize() const;
        std::string getSha1() const;
        std::string getPackAs() const;
        long getModified() const;

        void setFilepath(const std::string &sFilepath);
        void setFilesize(long nFilesize);
        void setSha1(const std::string &sSha1);
        void setPackAs(const std::string &sPackAs);
        void setModified(long nModified);

    private:
        std::string TAG;
        bool m_bHolded;
        std::string m_sFilepath;
        long m_nFilesize;
        std::string m_sSha1;
        std::string m_sPackAs;
        long m_nModified;
        WsjcppYamlNode *m_pYamlResourceFile;
};

#endif // WSJCPP_PACKAGE_MANAGER_RESOURCE_FILE_H