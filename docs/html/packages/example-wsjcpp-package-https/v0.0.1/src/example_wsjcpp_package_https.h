#ifndef EXAMPLE_WSJCPP_PACKAGE_HTTPS_H
#define EXAMPLE_WSJCPP_PACKAGE_HTTPS_H

#include <string>

class ExampleWsjcppPackageHttps {
    public:
        ExampleWsjcppPackageHttps();
        void setValue(const std::string &sValue);
        std::string getValue();
    private:
        std::string m_sValue;
};


#endif // EXAMPLE_WSJCPP_PACKAGE_HTTPS_H
