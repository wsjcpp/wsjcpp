#ifndef ARGUMENT_PROCESSOR_SOURCES_H
#define ARGUMENT_PROCESSOR_SOURCES_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorDistribution : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorDistribution();
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorDistributionList();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionAdd : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorDistributionAdd();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionRemove : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorDistributionRemove();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionUpdate : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorDistributionUpdate();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
    private:
        bool m_bUpdateAll;
        
};

#endif // ARGUMENT_PROCESSOR_SOURCES_H