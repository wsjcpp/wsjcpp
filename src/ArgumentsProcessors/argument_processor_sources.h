#ifndef ARGUMENT_PROCESSOR_SOURCES_H
#define ARGUMENT_PROCESSOR_SOURCES_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorSources : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorSources();
        
    private:
        
};

class ArgumentProcessorSourcesList : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorSourcesList();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorSourcesAdd : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorSourcesAdd();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorSourcesRemove : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorSourcesRemove();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_SOURCES_H