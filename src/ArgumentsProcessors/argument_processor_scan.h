#ifndef ARGUMENT_PROCESSOR_SCAN_H
#define ARGUMENT_PROCESSOR_SCAN_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorScan : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorScan();

        virtual bool applyParameterArgument(const std::string &sProgramName, const std::string &sArgumentName, const std::string &sValue);
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorScanTodo : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorScanTodo();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) override;
    private: 
};

class ArgumentProcessorScanUniqLines : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorScanUniqLines();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) override;
    private: 
};

#endif // ARGUMENT_PROCESSOR_SCAN_H
