#ifndef ARGUMENT_PROCESSOR_UNIT_TESTS_H
#define ARGUMENT_PROCESSOR_UNIT_TESTS_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorUnitTests : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUnitTests();
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsCreate : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsCreate();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsDelete : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsDelete();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
    private:
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsEnable : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsEnable();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:

};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsDisable : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsDisable();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsList();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsRun : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsRun();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_UNIT_TESTS_H
