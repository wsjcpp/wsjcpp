#ifndef ARGUMENT_PROCESSOR_BASIC_H
#define ARGUMENT_PROCESSOR_BASIC_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorInfo : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorInfo();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
    private:
        
};

#endif // ARGUMENT_PROCESSOR_BASIC_H