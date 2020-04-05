#ifndef WSJCPP_PACKAGE_MANAGER_SAFE_SCRIPTING_GENERATE_H
#define WSJCPP_PACKAGE_MANAGER_SAFE_SCRIPTING_GENERATE_H

#include <string>

// ---------------------------------------------------------------------

class WsjcppPackageManagerSafeScriptingGenerate {
    public:
        WsjcppPackageManagerSafeScriptingGenerate();
        std::string getName() const;
        std::string getFullPath() const;
        std::string getModuleName() const;
            
        void setName(const std::string &sName);
        void setFullPath(const std::string &sFullPath);
        void setModuleName(const std::string &sModuleName);

    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sFullPath;
        std::string m_sModuleName;
};

#endif // WSJCPP_PACKAGE_MANAGER_SAFE_SCRIPTING_GENERATE_H