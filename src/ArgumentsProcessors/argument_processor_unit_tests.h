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

#pragma once

#include <wsjcpp_arguments.h>

class ArgumentProcessorUnitTests : public WsjcppArgumentProcessor {
public:
  ArgumentProcessorUnitTests();
};

class ArgumentProcessorUnitTestsCreate : public WsjcppArgumentProcessor {
public:
  ArgumentProcessorUnitTestsCreate();
  virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorUnitTestsDelete : public WsjcppArgumentProcessor {
public:
  ArgumentProcessorUnitTestsDelete();
  virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorUnitTestsEnable : public WsjcppArgumentProcessor {
public:
  ArgumentProcessorUnitTestsEnable();
  virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorUnitTestsDisable : public WsjcppArgumentProcessor {
public:
  ArgumentProcessorUnitTestsDisable();
  virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorUnitTestsList : public WsjcppArgumentProcessor {
public:
  ArgumentProcessorUnitTestsList();
  virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorUnitTestsRun : public WsjcppArgumentProcessor {
public:
  ArgumentProcessorUnitTestsRun();
  virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};
