
#include "argument_processor_prepare.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>

// ---------------------------------------------------------------------
// ArgumentProcessorPrepare

ArgumentProcessorPrepare::ArgumentProcessorPrepare() 
: WsjcppArgumentProcessor({"prepare"}, "Preparing some files and packages for another systems") {
    TAG = "ArgumentProcessorPrepare";
    registryProcessor(new ArgumentProcessorPrepareTravis());
}

// ---------------------------------------------------------------------

bool ArgumentProcessorPrepare::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    WsjcppLog::err(TAG, "Not implemented");
    return false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorPrepare::applyParameterArgument(
    const std::string &sProgramName, 
    const std::string &sArgumentName, 
    const std::string &sValue
) {
    WsjcppLog::err(TAG, "Not implemented");
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorPrepare::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppLog::err(TAG, "Not implemented");
    return -1; 
}

// ---------------------------------------------------------------------
// ArgumentProcessorPrepareTravis

ArgumentProcessorPrepareTravis::ArgumentProcessorPrepareTravis() 
: WsjcppArgumentProcessor({"travis"}, "Prepare .travis.yml - Control file for Travis CI System") {
    TAG = "ArgumentProcessorPrepareTravis";
}

// ---------------------------------------------------------------------

int ArgumentProcessorPrepareTravis::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    if (WsjcppCore::fileExists(".travis.yml")) {
        std::cout 
            << std::endl
            << "ERROR: .travis.yml - file already exists" 
            << std::endl
            << std::endl;
        return -1; 
    }

    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout 
            << std::endl
            << "ERROR: Could not load package info from current directory"
            << std::endl
            << std::endl
        ;
        return -1;
    }

    std::string sContent = ""
        "language: cpp\n"
        "\n"
        "branches:\n"
        "  only:\n"
        "    - master\n"
        "\n"
        "dist: bionic\n"
        "\n"
        "addons:\n"
        "  apt:\n"
        "    packages:\n"
        "    - cmake\n"
        "    - make\n"
        "    - g++\n"
        "    - pkg-config\n"
        "\n"
        "# Build steps\n"
        "script:\n"
        "  - ./build_simple.sh\n"
        "  - cd unit-tests.wsjcpp\n"
        "  - ./build_simple.sh\n"
        "  - ./unit-tests\n"
    ;
    WsjcppCore::writeFile(".travis.yml", sContent);
    std::cout 
        << std::endl
        << "Create new file '.travis.yml'"
        << std::endl
        << std::endl
        << "Also you can add to README.md badge:"
        << std::endl
        << "   [![Build Status](https://api.travis-ci.com/USERNAME/REPO_NAME.svg?branch=master)](https://travis-ci.com/USERNAME/REPO_NAME) "
        << std::endl
        << "   Please replace USERNAME and REPO_NAME"
        << std::endl
        << std::endl
    ;
    return 0;
}
