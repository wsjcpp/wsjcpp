#include "argument_processor_authors.h"
#include <wsjcpp_package_manager.h>
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// ArgumentProcessorAuthors

ArgumentProcessorAuthors::ArgumentProcessorAuthors() 
: WsjcppArgumentProcessor({"authors", "ath"}, "Authors from the package", "Authors from the package") {
      registryProcessor(new ArgumentProcessorAuthorsList());
      registryProcessor(new ArgumentProcessorAuthorsAdd());
      registryProcessor(new ArgumentProcessorAuthorsRemove());
      registryProcessor(new ArgumentProcessorAuthorsTree());
}

// ---------------------------------------------------------------------

int ArgumentProcessorAuthors::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout << "Could not load package info from current directory" << std::endl;
        return -1;
    }
/*
    std::cout << std::endl 
        << "===== begin: wsjcpp info =====" << std::endl
        << "Name: " << pkg.getName() << std::endl
        << "Version: " << pkg.getVersion() << std::endl
        << "Description: " << pkg.getDescription()
        << std::endl;

    if (pkg.isHolded()) {
        std::cout << "Package is holded" << std::endl;
    }
    std::cout << "Directory: " << pkg.getDir() << std::endl;
    std::cout << "wsjcpp.version = " << pkg.getWsjcppVersion() << std::endl;
    // print keywords
    std::vector<std::string> vKeywords = pkg.getListOfKeywords();
    if (vKeywords.size() > 0) {
        std::cout << "Keywords: " << std::endl;
        for (unsigned int i = 0; i < vKeywords.size(); i++) {
            std::cout << " - " << vKeywords[i] << std::endl;
        }
    }

    std::vector<WsjcppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
    if (vFiles.size() > 0) {
        std::cout << std::endl << "Distribution-Files: " << std::endl;
        for (unsigned int i = 0; i < vFiles.size(); i++) {
            WsjcppPackageManagerDistributionFile source = vFiles[i];
            std::cout << " - " << source.getSourceFile() << " -> " << source.getTargetFile() << "[" << source.getType() << "]" << std::endl;
        }
    }
    
    std::vector<WsjcppPackageManagerAuthor> vAuthors = pkg.getListOfAuthors();
    if (vAuthors.size() > 0) { 
        std::cout << std::endl << "Authors: " << std::endl;
        for (unsigned int i = 0; i < vAuthors.size(); i++) {
            WsjcppPackageManagerAuthor author = vAuthors[i];
            std::cout << " - " << author.getName() << " <" << author.getEmail() << ">" << std::endl;
        }
    }
    
    std::vector<WsjcppPackageManagerDependence> vDeps = pkg.getListOfDependencies();
    if (vDeps.size() > 0) { 
        std::cout << std::endl << "Dependencies: " << std::endl;
        for (unsigned int i = 0; i < vDeps.size(); i++) {
            WsjcppPackageManagerDependence dep = vDeps[i];
            std::cout << " - " << dep.getName() << ":" << dep.getVersion() << std::endl;
        }
    }
    

    std::cout << "===== end: wsjcpp info =====" << std::endl
        << std::endl;
        */
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorAuthorsList

ArgumentProcessorAuthorsList::ArgumentProcessorAuthorsList() 
: WsjcppArgumentProcessor({"list", "ls"}, "Authors from the package", "Authors from the package") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorAuthorsList::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout << "Could not load package info from current directory" << std::endl;
        return -1;
    }

    if (vSubParams.size() != 0) {
        std::cout << "Expected no one params" << std::endl;
        return -1;
    }
    
    pkg.printAuthors();
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorAuthorsRemove

ArgumentProcessorAuthorsRemove::ArgumentProcessorAuthorsRemove() 
: WsjcppArgumentProcessor({"remove", "rm"}, "Remove author from the package", "Remove author from the package") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorAuthorsRemove::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout << "Could not load package info from current directory" << std::endl;
        return -1;
    }
    
    if (vSubParams.size() != 1) {
        std::cout << "Expected <full author name>" << std::endl;
        return -1;
    }
    std::string sFullAuthorName = vSubParams[0];

    if (!pkg.removeAuthor(sFullAuthorName)) {
        std::cout << "Failed" << std::endl;
        return -1;
    }
    pkg.save();
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorAuthorsAdd

ArgumentProcessorAuthorsAdd::ArgumentProcessorAuthorsAdd() 
: WsjcppArgumentProcessor({"add"}, "Add new author", "Add new author") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorAuthorsAdd::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout << "Could not load package info from current directory" << std::endl;
        return -1;
    }
    if (vSubParams.size() != 2) {
        std::cout << "Expected <author name> <author email>" << std::endl;
        return -1;
    }
    std::string sAuthorName = vSubParams[0];
    std::string sAuthorEmail = vSubParams[1];
    if (!pkg.addAuthor(sAuthorName, sAuthorEmail)) {
        return -1;
    }
    pkg.save();
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorAuthorsTree

ArgumentProcessorAuthorsTree::ArgumentProcessorAuthorsTree() 
: WsjcppArgumentProcessor({"tree", "tr"}, "Tree author's packages", "Tree author's packages") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorAuthorsTree::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout << "Could not load package info from current directory" << std::endl;
        return -1;
    }

    if (vSubParams.size() != 0) {
        std::cout << "Expected no one params" << std::endl;
        return -1;
    }
    pkg.printAuthorsTree();
    return 0;
}