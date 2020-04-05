#ifndef ARGUMENT_PROCESSOR_TEMPLATES_H
#define ARGUMENT_PROCESSOR_TEMPLATES_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorGenerate : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorGenerate();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);

    private:
        
};

class ArgumentProcessorGenerateList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorGenerateList();
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        bool m_bMore;
};

class ArgumentProcessorGenerateCreate : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorGenerateCreate();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorGenerateDelete : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorGenerateDelete();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_TEMPLATES_H