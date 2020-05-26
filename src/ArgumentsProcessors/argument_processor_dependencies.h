#ifndef ARGUMENT_PROCESSOR_DEPENDENCIES_H
#define ARGUMENT_PROCESSOR_DEPENDENCIES_H

#include <wsjcpp_arguments.h>
#include <wsjcpp_package_manager.h>

class ArgumentProcessorInstall : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorInstall();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        std::string TAG;
};

class ArgumentProcessorReinstall : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorReinstall();
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        bool m_bReinstallAll;
};

class ArgumentProcessorUninstall : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUninstall();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        
};

class ArgumentProcessorList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorList();
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
        bool m_bTree;
        std::string loadDependencies(
            const WsjcppPackageManager &rootPackage, 
            const WsjcppPackageManagerDependence &dep,
            const std::string &sIntent
        );
};

class ArgumentProcessorUpdate : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUpdate();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        std::string TAG;
};

#endif // ARGUMENT_PROCESSOR_DEPENDENCIES_H
