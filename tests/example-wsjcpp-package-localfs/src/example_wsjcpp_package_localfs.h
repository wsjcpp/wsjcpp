#ifndef EXAMPLE_WSJCPP_PACKAGE_LOCALFS_H
#define EXAMPLE_WSJCPP_PACKAGE_LOCALFS_H

#include <string>
#include "subfolder1/example_subfolder.h"

class ExampleWsjcppPackageLocalFs {
    public:
        ExampleWsjcppPackageLocalFs();
        void setValue(const std::string &sValue);
        std::string getValue();
    private:
        std::string m_sValue;
        ExampleSubfolder m_exampleSubfolder;
};


#endif // EXAMPLE_WSJCPP_PACKAGE_LOCALFS_H
