#ifndef WSJCPP_SAFE_SCRIPTING_H
#define WSJCPP_SAFE_SCRIPTING_H

#include <string>
#include <vector>
#include <map>

// ---------------------------------------------------------------------

class WsjcppSafeScriptingVariable {
    public:
        WsjcppSafeScriptingVariable(const std::string &sValue);
        std::string getValue();
        void setValue(const std::string &sValue);
    private:
        std::string TAG;
        std::string m_sValue;
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProc(const std::string &sProcName);
        std::string getName();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs);
    protected:
        std::string TAG;

    private:
        std::string m_sProcName;
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcLogInfo : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcLogInfo();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcedureSetValue : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcedureSetValue();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcedureConcat : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcedureConcat();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcMakeDir : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcMakeDir();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcNormalizeClassName : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcNormalizeClassName();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcCamelCaseToSnakeCase : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcCamelCaseToSnakeCase();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcToUpperCase : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcToUpperCase();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcWriteFile : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcWriteFile();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingProcCMakeListsTxtAppendWsjcpp : public WsjcppSafeScriptingProc {
    public:
        WsjcppSafeScriptingProcCMakeListsTxtAppendWsjcpp();
        virtual bool exec(const std::vector<WsjcppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingToken {
    public:
        WsjcppSafeScriptingToken(
            const std::string &sToken, 
            const std::string &sScriptName, // TODO repalce to pointer of script context
            int nNumberOfLine
        );
        std::string getToken(); // getTokenValue
        bool hasString();
        std::string getContextForLog();
    private:
        std::string TAG;
        std::string m_sToken;
        int m_nNumberOfLine;
        std::string m_sScriptName;
};

// ---------------------------------------------------------------------

class WsjcppSafeScriptingContext {
    public:
        WsjcppSafeScriptingContext();
        ~WsjcppSafeScriptingContext();

        WsjcppSafeScriptingVariable * addVariable(const std::string &sName);
        WsjcppSafeScriptingVariable * getVariable(const std::string &sName);
        bool hasVariable(const std::string &sName);
        bool hasVar(const std::string &sName);
        bool addProc(WsjcppSafeScriptingProc *pProcedure);
        WsjcppSafeScriptingProc *getProc(const std::string &sName);
        bool hasProc(const std::string &sName);
        
        int exec(
            const std::string &sScriptRootDir,
            const std::string &sScriptFileName,
            const std::string &sScriptContent,
            std::vector<std::string> vArgs
        );

    private:
        std::string TAG;
        std::string m_sScriptRootDir;
        std::string m_sScriptFileName;
        std::string m_sScriptContent;
        std::vector<WsjcppSafeScriptingToken *> m_vScriptTokens;
        bool parseScript();

        std::map<std::string, WsjcppSafeScriptingVariable *> m_vVariables;
        std::map<std::string, WsjcppSafeScriptingProc *> m_vProcs;
};

#endif // WSJCPP_SAFE_SCRIPTING_H


