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

#ifndef ARGUMENT_PROCESSOR_RESOURCES_H
#define ARGUMENT_PROCESSOR_RESOURCES_H

#include <wsjcpp_arguments.h>

// ---------------------------------------------------------------------

class ArgumentProcessorResources : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResources();

        virtual bool applyParameterArgument(const std::string &sProgramName, const std::string &sArgumentName, const std::string &sValue);
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

// ---------------------------------------------------------------------

class ArgumentProcessorResourcesList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResourcesList();

        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        bool m_bMore;
};

// ---------------------------------------------------------------------

class ArgumentProcessorResourcesRemove : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResourcesRemove();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

// ---------------------------------------------------------------------

class ArgumentProcessorResourcesAdd : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResourcesAdd();

        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        bool m_bText;
        bool m_bBinary;
};


// ---------------------------------------------------------------------

class ArgumentProcessorResourcesUpdate : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResourcesUpdate();

        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};
#endif // ARGUMENT_PROCESSOR_RESOURCES_H
