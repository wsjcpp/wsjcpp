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

#include "argument_processor_main.h"
#include "argument_processor_unit_tests.h"
#include "argument_processor_run.h"
#include "argument_processor_generate.h"
#include "argument_processor_dependencies.h"
#include "argument_processor_distribution.h"
#include "argument_processor_basic.h"
#include "argument_processor_origins.h"
#include "argument_processor_scan.h"
#include "argument_processor_prepare.h"
#include "argument_processor_resources.h"
#include "argument_processor_change.h"
#include "argument_processor_authors.h"
#include "argument_processor_lint.h"


#include <wsjcpp_package_manager.h>
#include <iostream>
#include <wsjcpp_core.h>

ArgumentProcessorMain::ArgumentProcessorMain() 
  : WsjcppArgumentProcessor({"main"}, "C++ Source Package Manager", "C++ Source Package Manager") {
    registryProcessor(new ArgumentProcessorVersion());
    registryProcessor(new ArgumentProcessorInfo());
    registryProcessor(new ArgumentProcessorChange());
    registryProcessor(new ArgumentProcessorInit());
    registryProcessor(new ArgumentProcessorClean());
    registryProcessor(new ArgumentProcessorScan());
    registryProcessor(new ArgumentProcessorInstall());
    registryProcessor(new ArgumentProcessorReinstall());
    registryProcessor(new ArgumentProcessorUninstall());
    registryProcessor(new ArgumentProcessorList());
    registryProcessor(new ArgumentProcessorUpdate());
    registryProcessor(new ArgumentProcessorVerify());
    registryProcessor(new ArgumentProcessorDistribution());
    // registryProcessor(new ArgumentProcessorRun());
    registryProcessor(new ArgumentProcessorGenerate());
    registryProcessor(new ArgumentProcessorUnitTests());
    // registryProcessor(new ArgumentProcessorOrigins());
    registryProcessor(new ArgumentProcessorPrepare());
    registryProcessor(new ArgumentProcessorResources());
    registryProcessor(new ArgumentProcessorAuthors());
    registryProcessor(new ArgumentProcessorLint());
    

    
}

// ---------------------------------------------------------------------

int ArgumentProcessorMain::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    // TODO help i think
    return -1;
}

// ---------------------------------------------------------------------
