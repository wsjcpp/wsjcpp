#ifndef ARGUMENT_PROCESSOR_AUTHORS_H
#define ARGUMENT_PROCESSOR_AUTHORS_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorAuthors : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorAuthors();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) override;
    private: 
};

class ArgumentProcessorAuthorsList : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorAuthorsList();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) override;
};

class ArgumentProcessorAuthorsRemove : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorAuthorsRemove();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) override;
};

class ArgumentProcessorAuthorsAdd : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorAuthorsAdd();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) override;
};

class ArgumentProcessorAuthorsTree : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorAuthorsTree();
        virtual int exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) override;
};

#endif // ARGUMENT_PROCESSOR_AUTHORS_H