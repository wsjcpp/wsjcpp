#ifndef ARGUMENT_PROCESSOR_RUN_H
#define ARGUMENT_PROCESSOR_RUN_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorRun : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorRun();
        
    private:
        
};

class ArgumentProcessorRunUnitTests : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorRunUnitTests();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorRunClean : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorRunClean();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorRunBuild : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorRunBuild();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_RUN_H