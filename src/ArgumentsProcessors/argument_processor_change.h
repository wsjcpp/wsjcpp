#ifndef ARGUMENT_PROCESSOR_CHANGE_H
#define ARGUMENT_PROCESSOR_CHANGE_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorChange : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorChange();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        
};

class ArgumentProcessorChangeVersion : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorChangeVersion();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
};

#endif // ARGUMENT_PROCESSOR_CHANGE_H