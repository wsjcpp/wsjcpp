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
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionAdd : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorDistributionAdd();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorDistributionRemove : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorDistributionRemove();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_SOURCES_H