#ifndef ARGUMENT_PROCESSOR_SOURCES_H
#define ARGUMENT_PROCESSOR_SOURCES_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorDistribution : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorDistribution();
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionList : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorDistributionList();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionAdd : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorDistributionAdd();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionRemove : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorDistributionRemove();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionUpdate : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorDistributionUpdate();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
    private:
        bool m_bUpdateAll;
        
};

#endif // ARGUMENT_PROCESSOR_SOURCES_H
