#ifndef EXAMPLE_WSJCPP_PACKAGE_LOCALFS_H
#define EXAMPLE_WSJCPP_PACKAGE_LOCALFS_H

#include <string>

class ExampleWsjcppPackageLocalFs {
    public:
        ExampleWsjcppPackageLocalFs();
        void setValue(const std::string &sValue);
        std::string getValue();
    private:
        std::string m_sValue;
};


#endif // EXAMPLE_WSJCPP_PACKAGE_LOCALFS_H
