#include "fallen_parse_args.h"
#include <iostream>
#include <algorithm>

// ---------------------------------------------------------------------

FallenParseArg::FallenParseArg(const std::string &sName, const std::string &sAlias, FallenParseArgType nType, const std::string &sDescription) {
     m_sName = sName;
     m_sAlias = sAlias;
     m_sDescription = sDescription;
     m_bIsOption = (nType == FallenParseArgType::PARAMETER);
}

// ---------------------------------------------------------------------

FallenParseArg::FallenParseArg() {
     m_sName = "";
     m_sAlias = "";
     m_sDescription = "";
     m_bIsOption = false;
 }

// ---------------------------------------------------------------------

std::string FallenParseArg::name() {
     return m_sName;
}
    
// ---------------------------------------------------------------------

std::string FallenParseArg::alias() {
     return m_sAlias;
}
    
// ---------------------------------------------------------------------

std::string FallenParseArg::description() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

bool FallenParseArg::isOption() {
    return m_bIsOption;
}

// ---------------------------------------------------------------------

FallenParseArgs::FallenParseArgs(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        m_vArgs.push_back(std::string(argv[i]));
    }
    // default args
    this->addHelp("help", "h", FallenParseArgType::SINGLE_OPTION, "This help");
    this->addHelp("version", "v", FallenParseArgType::SINGLE_OPTION, "Print version");
}

// ---------------------------------------------------------------------

void FallenParseArgs::setAppName(const std::string &sAppName) {
    m_sAppName = sAppName;
}

// ---------------------------------------------------------------------

std::string FallenParseArgs::appName() {
    return m_sAppName;
}

// ---------------------------------------------------------------------

void FallenParseArgs::setAppVersion(const std::string &sAppVersion) {
    m_sAppVersion = sAppVersion;
}

// ---------------------------------------------------------------------

std::string FallenParseArgs::appVersion() {
    return m_sAppVersion;
}

// ---------------------------------------------------------------------

std::string FallenParseArgs::option(const std::string &sName) {
    FallenParseArg *pHpa = NULL;
    for (unsigned int i = 0; i < m_vHelpArgs.size(); i++) {
        if (m_vHelpArgs[i]->name() == sName) {
            pHpa = m_vHelpArgs[i];
            break;
        }
    }
    if (pHpa == NULL) {
        std::cout << "Error: Not defined attribute \n";
        // Log::err(TAG, "Not defined attribute");
        return "";
    }

    if (!pHpa->isOption()) {
        std::cout << "Error: It's not option \n";
        return "";
    }

    std::vector<std::string>::iterator it1 = std::find(m_vArgs.begin(), m_vArgs.end(), pHpa->name());
    if (it1 != m_vArgs.end() && std::next(it1, 1) != m_vArgs.end()) {
        return * std::next(it1, 1);
    }

    std::vector<std::string>::iterator it2 = std::find(m_vArgs.begin(), m_vArgs.end(), pHpa->alias());
    if (it2 != m_vArgs.end() && std::next(it2, 1) != m_vArgs.end()) {
        return * std::next(it2, 1);
    }
    return "";
}

// ---------------------------------------------------------------------

bool FallenParseArgs::has(const std::string &sName) {
    std::vector<std::string> m_vAliases;
    m_vAliases.push_back(sName);
    FallenParseArg *pHpa = NULL;
    for (unsigned int i = 0; i < m_vHelpArgs.size(); i++) {
        if (m_vHelpArgs[i]->name() == sName) {
            pHpa = m_vHelpArgs[i];
            m_vAliases.push_back(pHpa->alias());
        }
    }
    if (pHpa == NULL) {
        std::cout << "Error: Not defined attribute for '" << sName << "'\n";
        // Log::err(TAG, "Not defined attribute");
        return false;
    }

    for (unsigned int i = 0; i < m_vAliases.size(); i++) {
        std::string sAlias = m_vAliases[i];
        std::vector<std::string>::iterator it = std::find(m_vArgs.begin(), m_vArgs.end(), sAlias);
        if (it != m_vArgs.end()) {
            // std::cout << "Found " + sAlias << ", " << pHpa->name() << ", " << (pHpa->isOption() ? "option" : "not option") <<  " \n";
            
        }
        if (it != m_vArgs.end() && !pHpa->isOption()) {
            return true;
        }

        if (pHpa->isOption() && it != m_vArgs.end() && std::next(it, 1) != m_vArgs.end()) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

void FallenParseArgs::addHelp(const std::string &sName, const std::string &sAlias, FallenParseArgType nType, const std::string &sDescription) {
    m_vHelpArgs.push_back(new FallenParseArg(sName, sAlias, nType, sDescription));
}

// ---------------------------------------------------------------------

void FallenParseArgs::printHelp() {
    // TODO calculate max size
    int nMaxSize = 0;
    for (unsigned int i = 0; i < m_vHelpArgs.size(); i++) {
        FallenParseArg *pHpa = m_vHelpArgs[i];
        std::string sTmp = pHpa->name() + ", " + pHpa->alias();
        nMaxSize = std::max(nMaxSize, (int)sTmp.size());
    }
    nMaxSize += 4;

    // TODO:
    std::cout << "" << m_sAppName << ":" << m_sAppVersion << "\n";
    std::cout << "Usage: " << m_vArgs.at(0) << "   [PARAM]\n";
    for (unsigned int i = 0; i < m_vHelpArgs.size(); i++) {
        FallenParseArg *pHpa = m_vHelpArgs[i];
        std::string sTmp = pHpa->name() + ", " + pHpa->alias();
        int nIntent = nMaxSize - sTmp.size();

        std::cout << "\t " << sTmp;
        for (int x = 0; x < nIntent; x++) {
            std::cout << " ";
        }
        std::cout << pHpa->description() << "\n";
    }

    std::cout << "\n";
}

// ---------------------------------------------------------------------

bool FallenParseArgs::checkArgs(std::string &sArgsErrors) {
    // TODO 
    return true;
}

// ---------------------------------------------------------------------

bool FallenParseArgs::handleDefault() {
    if (this->has("help")) {
        this->printHelp();
        return 0;
    } else if (this->has("version")) {
        std::cout << m_sAppName << "-" << m_sAppVersion << "\n";
        return 0;
    }
    return false;
}