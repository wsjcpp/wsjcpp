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

#include "argument_processor_run.h"
#include "wsjcpp_package_manager.h"

ArgumentProcessorRun::ArgumentProcessorRun() 
  : WsjcppArgumentProcessor({"run"}, "Run basic scripts", "run clean/build/unit-tests scripts") {
      registryProcessor(new ArgumentProcessorRunUnitTests());
      registryProcessor(new ArgumentProcessorRunClean());
      registryProcessor(new ArgumentProcessorRunBuild());
}

// ---------------------------------------------------------------------

ArgumentProcessorRunUnitTests::ArgumentProcessorRunUnitTests() 
  : WsjcppArgumentProcessor({"unit-tests"}, "Build and run unit-tests", "Build and run unit-tests") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunUnitTests::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorRunClean::ArgumentProcessorRunClean() 
  : WsjcppArgumentProcessor({"clean"}, "Run clean script", "do run clean.sh script") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunClean::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorRunBuild::ArgumentProcessorRunBuild() 
  : WsjcppArgumentProcessor({"build"}, "run build.sh script", "do run 'build_simple.sh' script") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunBuild::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------