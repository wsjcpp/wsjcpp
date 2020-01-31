#ifndef WSJCPP_ARGUMENTS_H
#define WSJCPP_ARGUMENTS_H

#include <string>
#include <vector>
#include <map>

class WSJCppArgumentSingle {
    public:
        WSJCppArgumentSingle(const std::string &sName, const std::string &sDescription);
        std::string getName();
        std::string getDescription();
        std::string help(const std::string &sProgramName, const std::string &sPrefix);

    private:
        std::string TAG;
        std::string m_sName;
        std::string m_sDescription;
};

// ---------------------------------------------------------------------

class WSJCppArgumentParameter {
    public:
        WSJCppArgumentParameter(const std::string &sName, const std::string &sDescription);
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

class WSJCppArgumentProcessor {
    public:
        WSJCppArgumentProcessor(const std::string &sName, const std::string &sDescription);
        WSJCppArgumentProcessor(const std::vector<std::string> &vNames, const std::string &sDescription);
        std::string getName();
        std::string getDescription();

        void registryProcessor(WSJCppArgumentProcessor *p);
        void registryExample(const std::string &sExample);
        void registrySingleArgument(const std::string &sArgumentName, const std::string &sDescription);
        void registryParameterArgument(const std::string &sArgumentName, const std::string &sDescription);
        WSJCppArgumentProcessor *findRegisteredProcessor(const std::string &sArgumentName);
        WSJCppArgumentSingle *findRegisteredSingleArgument(const std::string &sArgumentName);
        WSJCppArgumentParameter *findRegisteredParameterArgument(const std::string &sArgumentName);

        bool hasRegisteredArgumentName(const std::string &sArgumentName);

        std::string help(const std::string &sProgramName, const std::string &sPrefix);
        
        bool getValueOfParam(const std::string &sArgumentName);

        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual bool applyParameterArgument(const std::string &sProgramName, const std::string &sArgumentName, const std::string &sValue);
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);

    protected:
        std::string TAG;

    private:
        std::string m_sName;
        std::vector<std::string> vNames;
        std::string m_sDescription;
        std::vector<WSJCppArgumentProcessor *> m_vProcessors;
        std::vector<WSJCppArgumentSingle *> m_vSingleArguments;
        std::vector<WSJCppArgumentParameter *> m_vParameterArguments;
        std::vector<std::string> m_vExamples;
};

// ---------------------------------------------------------------------

class WSJCppArgumentsSpliter {
    public:
        WSJCppArgumentsSpliter(WSJCppArgumentProcessor *pArgumentProcessor, const std::vector<std::string> &vParams);
        std::vector<std::string> getSingleAgruments();
        std::vector<std::string> getParamsArguments();

    private:
        std::vector<std::string> m_vOriginalParams;
        std::vector<std::string> m_vSingleArguments;
        std::vector<std::string> m_vParamsArguments;
};


// ---------------------------------------------------------------------

class WSJCppArguments {
    public:
        WSJCppArguments(int argc, const char* argv[], WSJCppArgumentProcessor *pRoot);
        int exec();
        std::string help();

    private:
        WSJCppArgumentProcessor *m_pRoot;
        std::vector<std::string> extractSingleAndParameterArguments(
            WSJCppArgumentProcessor *pArgumentProcessor, 
            const std::vector<std::string> &vArguments,
            std::vector<WSJCppArgumentSingle *> &vSingleArguments,
            std::vector<WSJCppArgumentParameter *> &vParameterArguments
        );
        int recursiveExec(WSJCppArgumentProcessor *pArgumentProcessor, std::vector<std::string> &vSubArguments);

        std::string TAG;
        std::vector<std::string> m_vArguments;
        std::string m_sProgramName;
        std::vector<WSJCppArgumentProcessor *> m_vProcessors;
};

// ---------------------------------------------------------------------

#endif // WSJCPP_ARGUMENTS_H


