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

#ifndef ARGUMENT_PROCESSOR_DEPENDENCIES_H
#define ARGUMENT_PROCESSOR_DEPENDENCIES_H

#include <wsjcpp_arguments.h>
#include <wsjcpp_package_manager.h>

class ArgumentProcessorInstall : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorInstall();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        std::string TAG;
};

class ArgumentProcessorReinstall : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorReinstall();
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        bool m_bReinstallAll;
};

class ArgumentProcessorUninstall : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUninstall();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        
};

class ArgumentProcessorList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorList();
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        bool m_bTree;
        std::string loadDependencies(
            const WsjcppPackageManager &rootPackage, 
            const WsjcppPackageManagerDependence &dep,
            const std::string &sIntent
        );
};

class ArgumentProcessorUpdate : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUpdate();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
};

#endif // ARGUMENT_PROCESSOR_DEPENDENCIES_H
