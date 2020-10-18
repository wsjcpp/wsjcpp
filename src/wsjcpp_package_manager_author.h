#ifndef WSJCPP_PACKAGE_MANAGER_AUTHOR_H
#define WSJCPP_PACKAGE_MANAGER_AUTHOR_H

#include <string>
#include <wsjcpp_yaml.h>

class WsjcppPackageManagerAuthor {
    public:
        WsjcppPackageManagerAuthor();
        WsjcppPackageManagerAuthor(const std::string &sName, const std::string &sEmail);
        bool fromYAML(WsjcppYamlNode *pYamlAuthor);
        WsjcppYamlNode *toYAML();

        std::string getName();
        std::string getEmail();
        std::string getWebSite();
        std::string getFullAuthor(); 

    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sEmail;
        std::string m_sWebSite;
        WsjcppYamlNode *m_pYamlAuthor;
};


#endif // WSJCPP_PACKAGE_MANAGER_AUTHOR_H