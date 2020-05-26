#ifndef ARGUMENT_PROCESSOR_RESOURCES_H
#define ARGUMENT_PROCESSOR_RESOURCES_H

#include <wsjcpp_arguments.h>

// ---------------------------------------------------------------------

class ArgumentProcessorResources : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResources();

        virtual bool applyParameterArgument(const std::string &sProgramName, const std::string &sArgumentName, const std::string &sValue);
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

// ---------------------------------------------------------------------

class ArgumentProcessorResourcesList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResourcesList();

        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        bool m_bMore;
};

// ---------------------------------------------------------------------

class ArgumentProcessorResourcesRemove : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResourcesRemove();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);
};

// ---------------------------------------------------------------------

class ArgumentProcessorResourcesAdd : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorResourcesAdd();

        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams);

    private:
        bool m_bText;
        bool m_bBinary;
};

#endif // ARGUMENT_PROCESSOR_RESOURCES_H
