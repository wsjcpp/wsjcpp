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

#ifndef WSJCPP_PACKAGE_MANAGER_DEPENDENCE_H
#define WSJCPP_PACKAGE_MANAGER_DEPENDENCE_H

#include <string>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------

class WsjcppPackageManagerDependence {
    public:
        WsjcppPackageManagerDependence();
        std::string getInstallationDir() const;
        std::string getUrl() const;
        std::string getName() const;
        std::string getVersion() const;
        std::string getOrigin() const;

        void setName(const std::string &sName);
        void setVersion(const std::string &sVersion);
        void setUrl(const std::string &sUrl);
        void setInstallationDir(const std::string &sInstallationDir);
        void setOrigin(const std::string &sOrigin);

        bool fromYAML(WsjcppYamlNode *pYaml);
        WsjcppYamlNode *toYAML();

    private:
        std::string TAG;
        std::string m_sInstallationDir;
        std::string m_sInstallationDateTime;
        std::string m_sUrl;
        std::string m_sName;
        std::string m_sVersion;
        std::string m_sOrigin;
        WsjcppYamlNode *m_pYamlDependece;
};

// ---------------------------------------------------------------------

#endif // WSJCPP_PACKAGE_MANAGER_DEPENDENCE_H