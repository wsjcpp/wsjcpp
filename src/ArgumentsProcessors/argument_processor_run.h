#ifndef ARGUMENT_PROCESSOR_RUN_H
#define ARGUMENT_PROCESSOR_RUN_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorRun : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorRun();
        
    private:
        
};

class ArgumentProcessorRunUnitTests : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorRunUnitTests();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorRunClean : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorRunClean();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorRunBuild : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorRunBuild();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_RUN_H