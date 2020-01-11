#ifndef ARGUMENT_PROCESSOR_DEPENDENCIES_H
#define ARGUMENT_PROCESSOR_DEPENDENCIES_H

#include <wsjcpp_arguments.h>

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
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);

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

#endif // ARGUMENT_PROCESSOR_DEPENDENCIES_H