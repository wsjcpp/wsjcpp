#ifndef ARGUMENT_PROCESSOR_MAIN_H
#define ARGUMENT_PROCESSOR_MAIN_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorMain : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorMain();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};


#endif // ARGUMENT_PROCESSOR_MAIN_H