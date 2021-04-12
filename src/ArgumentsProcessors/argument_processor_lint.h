#ifndef ARGUMENT_PROCESSOR_LINT_H
#define ARGUMENT_PROCESSOR_LINT_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorLint : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorLint();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
    private:
        bool isEndsWith(std::string const &sValue, std::string const &sEnding);
        
};

#endif // ARGUMENT_PROCESSOR_LINT_H