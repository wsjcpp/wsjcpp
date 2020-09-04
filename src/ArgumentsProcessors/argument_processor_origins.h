#ifndef ARGUMENT_PROCESSOR_ORIGINS_H
#define ARGUMENT_PROCESSOR_ORIGINS_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorOrigins : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorOrigins();
        
    private:
        
};

class ArgumentProcessorOriginsAdd : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorOriginsAdd();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorOriginsRemove : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorOriginsRemove();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorOriginsList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorOriginsList();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_ORIGINS_H