#ifndef WSJCPP_ARGUMENTS_H
#define WSJCPP_ARGUMENTS_H

#include <string>
#include <vector>
#include <map>

class WsjcppArgumentSingle {
    public:
        WsjcppArgumentSingle(const std::string &sName, const std::string &sDescription);
        std::string getName();
        std::string getDescription();
        std::string help(const std::string &sProgramName, const std::string &sPrefix);

    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sDescription;
};

// ---------------------------------------------------------------------

class WsjcppArgumentParameter {
    public:
        WsjcppArgumentParameter(const std::string &sName, const std::string &sDescription);
        std::string getName();
        std::string getDescription();
        std::string getValue();
        void setValue(const std::string &sValue);
        std::string help(const std::string &sProgramName, const std::string &sPrefix);

    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sValue;
        std::string m_sDescription;
};

// ---------------------------------------------------------------------

class WsjcppArgumentProcessor {
    public:
        WsjcppArgumentProcessor(const std::vector<std::string> &vNames, const std::string &sDescription);
        const std::vector<std::string> &getNames();
        std::string getNamesAsString();
        std::string getDescription();

        void registryProcessor(WsjcppArgumentProcessor *p);
        void registryExample(const std::string &sExample);
        void registrySingleArgument(const std::string &sArgumentName, const std::string &sDescription);
        void registryParameterArgument(const std::string &sArgumentName, const std::string &sDescription);
        WsjcppArgumentProcessor *findRegisteredProcessor(const std::string &sArgumentName);
        WsjcppArgumentSingle *findRegisteredSingleArgument(const std::string &sArgumentName);
        WsjcppArgumentParameter *findRegisteredParameterArgument(const std::string &sArgumentName);

        bool hasRegisteredArgumentName(const std::string &sArgumentName);

        std::string help(const std::string &sProgramName, const std::string &sPrefix);
        
        bool getValueOfParam(const std::string &sArgumentName);

        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual bool applyParameterArgument(const std::string &sProgramName, const std::string &sArgumentName, const std::string &sValue);
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);

    protected:
        std::string TAG;

    private:
        std::vector<std::string> m_vNames;
        std::string m_sDescription;
        std::vector<WsjcppArgumentProcessor *> m_vProcessors;
        std::vector<WsjcppArgumentSingle *> m_vSingleArguments;
        std::vector<WsjcppArgumentParameter *> m_vParameterArguments;
        std::vector<std::string> m_vExamples;
};

// ---------------------------------------------------------------------

class WsjcppArgumentsSpliter {
    public:
        WsjcppArgumentsSpliter(WsjcppArgumentProcessor *pArgumentProcessor, const std::vector<std::string> &vParams);
        std::vector<std::string> getSingleAgruments();
        std::vector<std::string> getParamsArguments();

    private:
        std::vector<std::string> m_vOriginalParams;
        std::vector<std::string> m_vSingleArguments;
        std::vector<std::string> m_vParamsArguments;
};


// ---------------------------------------------------------------------

class WsjcppArguments {
    public:
        WsjcppArguments(int argc, const char* argv[], WsjcppArgumentProcessor *pRoot);
        ~WsjcppArguments();
        int exec();
        std::string help();

    private:
        WsjcppArgumentProcessor *m_pRoot;
        std::vector<std::string> extractSingleAndParameterArguments(
            WsjcppArgumentProcessor *pArgumentProcessor, 
            const std::vector<std::string> &vArguments,
            std::vector<WsjcppArgumentSingle *> &vSingleArguments,
            std::vector<WsjcppArgumentParameter *> &vParameterArguments
        );
        int recursiveExec(WsjcppArgumentProcessor *pArgumentProcessor, std::vector<std::string> &vSubArguments);

        std::string TAG;
        std::vector<std::string> m_vArguments;
        std::string m_sProgramName;
        std::vector<WsjcppArgumentProcessor *> m_vProcessors;
};

// ---------------------------------------------------------------------

#endif // WSJCPP_ARGUMENTS_H

