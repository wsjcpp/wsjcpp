#ifndef ARGUMENT_PROCESSOR_ORIGINS_H
#define ARGUMENT_PROCESSOR_ORIGINS_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorOrigins : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorOrigins();
        
    private:
        
};

class ArgumentProcessorOriginsAdd : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorOriginsAdd();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorOriginsRemove : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorOriginsRemove();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorOriginsList : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorOriginsList();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_ORIGINS_H