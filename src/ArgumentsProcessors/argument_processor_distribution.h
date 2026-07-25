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

#ifndef ARGUMENT_PROCESSOR_SOURCES_H
#define ARGUMENT_PROCESSOR_SOURCES_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorDistribution : public WsjcppArgumentProcessor {
public:
    ArgumentProcessorDistribution();
private:
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionList : public WsjcppArgumentProcessor {
public:
    ArgumentProcessorDistributionList();
    virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
private:
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionAdd : public WsjcppArgumentProcessor {
public:
    ArgumentProcessorDistributionAdd();
    virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
private:
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionRemove : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorDistributionRemove();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_SOURCES_H