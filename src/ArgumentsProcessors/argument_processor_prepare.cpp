
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
    registryProcessor(new ArgumentProcessorPrepareDockerfile());
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


// ---------------------------------------------------------------------
// ArgumentProcessorPrepareDockerfile

ArgumentProcessorPrepareDockerfile::ArgumentProcessorPrepareDockerfile() 
: WsjcppArgumentProcessor({"dockerfile"}, "Prepare sample of Dockerfile for build and publish current project") {
    TAG = "ArgumentProcessorPrepareDockerfile";
}

// ---------------------------------------------------------------------

int ArgumentProcessorPrepareDockerfile::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
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
    // TODO just call merge ignorefile for .gtiignore and for .dockerignore
    std::string sContentDockerignore = 
        ".wsjcpp/*\n"
        ".vscode/*\n"
        ".DS_Store/*\n"
        "tmp/*\n"
        "unit-tests.wsjcpp/*\n"
    ;

    std::string sContentDockerfile = 
        "# " + pkg.getName() + "@" + pkg.getVersion() + "\n"
        "FROM debian:10\n"
        "\n"
        "# install build requiremenets\n"
        "RUN apt update && apt install -y --no-install-recommends \\\n"
        "  build-essential \\\n"
        "  make \\\n"
        "  cmake \\\n"
        "  gcc \\\n"
        "  g++ \\\n"
        "  pkg-config \\\n"
        "  git-core \n"
        "\n"
        "COPY . /root/source-code\n"
        "RUN cd /root/src \\\n"
        "  && mkdir -p tmp.docker \\\n"
        "  && cd tmp.docker \\\n"
        "  && cmake .. \\\n"
        "  && make \n"
        "\n"
        "\n"
        "# now do release image \n"
        "FROM debian:10\n"
        " # LABEL \"maintainer\"=\"Maintainer Name <mantainer@mail>\"\n"
        " # LABEL \"repository\"=\"https://maintainer repository\"\n"
        "\n"
        "RUN apt-get update && apt-get install -y \\\n"
        "  locales \n"
        "\n"
        "# fix for libcurl (on send mail)\n"
        "RUN sed -i -e \"s/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/\" /etc/locale.gen && \\\n"
        "    echo 'LANG=\"en_US.UTF-8\"'>/etc/default/locale && \\\n"
        "    dpkg-reconfigure --frontend=noninteractive locales && \\\n"
        "    update-locale LANG=en_US.UTF-8\n"
        "\n"
        "COPY --from=0 /root/source-code/" +  pkg.getName() + " /usr/bin/" +  pkg.getName() + "\n"
        "RUN mkdir -p /root/app \\\n"
        "\n"
        "WORKDIR /root/app\n"
        "\n"
        "# if need: expose tcp port of service\n"
        "# EXPOSE 1234 4613 7080\n"
        "\n"
        "CMD " +  pkg.getName() + " start\n"
    ;

    if (!WsjcppCore::fileExists("Dockerfile")) {
        WsjcppCore::writeFile("./Dockerfile", sContentDockerfile);
        std::cout << "Dockerfile: created" << std::endl;
    } else {
        std::cout << "Dockerfile: skipped already exists" << std::endl;
    }

    if (!WsjcppCore::fileExists(".dockerignore")) {
        WsjcppCore::writeFile("./.dockerignore", sContentDockerignore);
        std::cout << ".dockerignore: created" << std::endl;
    } else {
        std::cout << ".dockerignore: skipped already exists" << std::endl;
    }

    std::cout << std::endl;
    return 0;
}