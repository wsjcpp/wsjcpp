#ifndef FALLEN_PARSE_ARGS
#define FALLEN_PARSE_ARGS

#include <string>
#include <vector>

// ---------------------------------------------------------------------

enum FallenParseArgType {
    PARAMETER,
    SINGLE_OPTION
};
        
// ---------------------------------------------------------------------

class FallenParseArg {
    public:
        // TODO redesign to alias list {"1", "2"}
        FallenParseArg(const std::string &sName, const std::string &sAlias, FallenParseArgType nType, const std::string &sDescription);
        FallenParseArg();
        std::string name();
        std::string alias();
        std::string description();
        bool isOption();

    private:
        std::string m_sName;
        std::string m_sAlias;
        std::string m_sDescription;
        bool m_bIsOption;
};

// ---------------------------------------------------------------------

class FallenParseArgs {
    public:
        FallenParseArgs(int argc, char** argv);
        void setAppName(const std::string &sAppName);
        std::string appName();
        void setAppVersion(const std::string &sAppVersion);
        std::string appVersion();
        bool has(const std::string &sName);
        std::string option(const std::string &sName);
        void addHelp(const std::string &sName, const std::string &sAlias, FallenParseArgType nType, const std::string &sDescription);
        void printHelp();
        bool handleDefault();
        bool checkArgs(std::string &sArgsErrors);

    private:
        std::vector<std::string> m_vArgs;
        std::vector<FallenParseArg *> m_vHelpArgs;
        std::string m_sAppName;
        std::string m_sAppVersion;
};

#endif // FALLEN_PARSE_ARGS