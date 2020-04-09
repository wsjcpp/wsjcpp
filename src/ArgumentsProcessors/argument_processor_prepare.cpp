
#include "argument_processor_prepare.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>

// ---------------------------------------------------------------------
// ArgumentProcessorPrepare

ArgumentProcessorPrepare::ArgumentProcessorPrepare() 
: WsjcppArgumentProcessor({"prepare"}, "Preparing some files and packages for another systems") {
    TAG = "ArgumentProcessorPrepare";
    registryProcessor(new ArgumentProcessorPrepareTravis());
    registryProcessor(new ArgumentProcessorPrepareHomebrew());
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
        << "Created new file '.travis.yml'"
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

// ---------------------------------------------------------------------
// ArgumentProcessorPrepareHomebrew

ArgumentProcessorPrepareHomebrew::ArgumentProcessorPrepareHomebrew() 
: WsjcppArgumentProcessor({"homebrew"}, "Prepare specific file for homebrew - Package Manager for MacOS") {
    TAG = "ArgumentProcessorPrepareTravis";
}

// ---------------------------------------------------------------------

int ArgumentProcessorPrepareHomebrew::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
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
    

    std::string sMainRepository = "";
    std::vector<WsjcppPackageManagerRepository> repos = pkg.getListOfRepositories();
    for (int i = 0; i < repos.size(); i++) {
        if (repos[i].getType() == "main") {
            sMainRepository = repos[i].getUrl();
        }
    }

    if (sMainRepository == "") {
        std::cout 
            << std::endl
            << "ERROR: Could not find main repository in wsjcpp.yml"
            << std::endl
            << std::endl
        ;
        return -1;
    }

    // sMainRepository.starts_with(std::string_view("https:://github.com/"));


    std::string sOutputDirectory = "homebrew-" + pkg.getName();
    WsjcppCore::makeDir(sOutputDirectory);

    std::string sContent = 
        "class " + pkg.getName() + " < Formula\n"
        "  desc \"" + pkg.getDescription() + "\"\n"
        "  homepage \"" + sMainRepository + "\"\n"
        "  url \"" + sMainRepository + "/archive/" + pkg.getVersion() + ".tar.gz\"\n"
        "  sha256 \"todo shasum -a 256 " + pkg.getVersion() + ".tar.gz\"\n"
        "  head \"" + sMainRepository + ".git\", :branch => \"master\"\n"
        "\n"
        "  bottle do\n"
        "    cellar :any\n"
        "    rebuild 1\n"
        "  end\n"
        "\n"
        "  depends_on \"cmake\"\n"
        "  depends_on \"pkg-config\"\n" // TODO add required packages
        "  depends_on :xcode\n"
        "\n"
        "  def install\n"
        "    bin.mkpath\n"
        "    system \"cmake\", \"-DCMAKE_INSTALL_PREFIX:PATH=#{prefix}\", \".\"\n"
        "    system \"make\"\n"
        "    bin.install \"" + pkg.getName() + "\"\n"
        "    bin.install_symlink\n"
        "  end\n"
        "\n"
        "  test do\n"
        "    system bin/\"" + pkg.getName() + "\", \"version\"\n"
        "  end\n"
        "end\n"
    ;

    std::string sHomebrewFilename = sOutputDirectory + "/" + pkg.getName() + ".rb";
    WsjcppCore::writeFile(sHomebrewFilename, sContent);
    std::cout 
        << std::endl
        << "Created/Updated new file '" << sHomebrewFilename << "'"
        << std::endl
        << std::endl
        << "Step 1. Make new release '" << pkg.getVersion() << "' in repository '" << sMainRepository << "' "
        << std::endl
        << "Step 2. Download archive: 'wget " << sMainRepository << "/archive/" << pkg.getVersion() << ".tar.gz'"
        << std::endl
        << "Step 3. Calculate 'shasum -a 256 " << pkg.getVersion() << ".gz'"
        << std::endl
        << "Step 4. Update field 'sha256' in '" << sHomebrewFilename << "'"
        << std::endl
        << "Step 5. Create new repository 'https:://github.com/USERNAME/homebrew-" << pkg.getName() << "' (if not exists) "
        << std::endl
        << "Step 6. Push file '" << sHomebrewFilename << "' to repository 'https:://github.com/USERNAME/homebrew-" << pkg.getName() << "'"
        << std::endl
        << "Step 7.  Add to readme how to install from brew tap:"
        << std::endl
        << "```"
        << std::endl
        << "% brew tap USERNAME/" << pkg.getName() << "'"
        << std::endl
        << "% brew install " << pkg.getName() << ""
        << std::endl
        << "```"
        << std::endl
        << std::endl
        << "Also you can run homebrew checks: 'brew audit --strict " << pkg.getName() << "'"
        << std::endl
        << std::endl
    ;

    return 0;
}