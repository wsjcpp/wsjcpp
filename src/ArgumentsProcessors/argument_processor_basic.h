#ifndef ARGUMENT_PROCESSOR_BASIC_H
#define ARGUMENT_PROCESSOR_BASIC_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorInfo : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorInfo();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
    private:
        
};

class ArgumentProcessorInit : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorInit();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
    private:
        
};

class ArgumentProcessorClean : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorClean();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
    private:
        
};

class ArgumentProcessorVersion : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorVersion();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) override;
    private: 
};

#endif // ARGUMENT_PROCESSOR_BASIC_H