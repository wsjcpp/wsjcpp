#ifndef ARGUMENT_PROCESSOR_DEPENDENCIES_H
#define ARGUMENT_PROCESSOR_DEPENDENCIES_H

#include <wsjcpp_arguments.h>
#include <wsjcpp_package_manager.h>

class ArgumentProcessorInstall : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorInstall();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        std::string TAG;
};

class ArgumentProcessorReinstall : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorReinstall();
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        bool m_bReinstallAll;
};

class ArgumentProcessorUninstall : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorUninstall();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        
};

class ArgumentProcessorList : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorList();
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        bool m_bTree;
        std::string loadDependencies(
            const WSJCppPackageManager &rootPackage, 
            const WSJCppPackageManagerDependence &dep,
            const std::string &sIntent
        );
};

class ArgumentProcessorUpdateGen : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorUpdateGen();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
};

#endif // ARGUMENT_PROCESSOR_DEPENDENCIES_H
