#ifndef ARGUMENT_PROCESSOR_UNIT_TESTS_H
#define ARGUMENT_PROCESSOR_UNIT_TESTS_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorUnitTests : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorUnitTests();
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsCreate : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsCreate();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsDelete : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsDelete();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsEnable : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsEnable();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

// ---------------------------------------------------------------------

class ArgumentProcessorUnitTestsDisable : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsDisable();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

class ArgumentProcessorUnitTestsList : public WSJCppArgumentProcessor {
    public:
        ArgumentProcessorUnitTestsList();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
        
    private:
        
};

#endif // ARGUMENT_PROCESSOR_UNIT_TESTS_H
