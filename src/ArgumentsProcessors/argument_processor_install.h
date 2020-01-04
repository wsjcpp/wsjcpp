#ifndef ARGUMENT_PROCESSOR_INSTALL_H
#define ARGUMENT_PROCESSOR_INSTALL_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorInstall : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorInstall();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        std::string TAG;
};


#endif // ARGUMENT_PROCESSOR_INSTALL_H