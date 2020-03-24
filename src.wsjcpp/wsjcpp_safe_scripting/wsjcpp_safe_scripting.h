#ifndef WSJCPP_SAFE_SCRIPTING_H
#define WSJCPP_SAFE_SCRIPTING_H

#include <string>
#include <vector>
#include <map>

// ---------------------------------------------------------------------

class WSJCppSafeScriptingVariable {
    public:
        WSJCppSafeScriptingVariable(const std::string &sValue);
        std::string getValue();
        void setValue(const std::string &sValue);
    private:
        std::string TAG;
        std::string m_sValue;
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProc(const std::string &sProcName);
        std::string getName();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs);
    protected:
        std::string TAG;

    private:
        std::string m_sProcName;
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcLogInfo : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcLogInfo();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcedureSetValue : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcedureSetValue();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcedureConcat : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcedureConcat();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcMakeDir : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcMakeDir();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcNormalizeClassName : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcNormalizeClassName();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcCamelCaseToSnakeCase : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcCamelCaseToSnakeCase();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcToUpperCase : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcToUpperCase();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcWriteFile : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcWriteFile();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingProcCMakeListsTxtAppendWSJCpp : public WSJCppSafeScriptingProc {
    public:
        WSJCppSafeScriptingProcCMakeListsTxtAppendWSJCpp();
        virtual bool exec(const std::vector<WSJCppSafeScriptingVariable *> &m_vArgs);
};

// ---------------------------------------------------------------------

class WSJCppSafeScriptingToken {
    public:
        WSJCppSafeScriptingToken(
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

class WSJCppSafeScriptingContext {
    public:
        WSJCppSafeScriptingContext();
        ~WSJCppSafeScriptingContext();

        WSJCppSafeScriptingVariable * addVariable(const std::string &sName);
        WSJCppSafeScriptingVariable * getVariable(const std::string &sName);
        bool hasVariable(const std::string &sName);
        bool hasVar(const std::string &sName);
        bool addProc(WSJCppSafeScriptingProc *pProcedure);
        WSJCppSafeScriptingProc *getProc(const std::string &sName);
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
        std::vector<WSJCppSafeScriptingToken *> m_vScriptTokens;
        bool parseScript();

        std::map<std::string, WSJCppSafeScriptingVariable *> m_vVariables;
        std::map<std::string, WSJCppSafeScriptingProc *> m_vProcs;
};

#endif // WSJCPP_SAFE_SCRIPTING_H


