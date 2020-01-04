#ifndef ARGUMENT_PROCESSOR_TEMPLATES_H
#define ARGUMENT_PROCESSOR_TEMPLATES_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorTemplates : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorTemplates();
        
    private:
        
};

class ArgumentProcessorTemplatesList : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorTemplatesList();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorTemplatesCreate : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorTemplatesCreate();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorTemplatesDelete : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorTemplatesDelete();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_TEMPLATES_H