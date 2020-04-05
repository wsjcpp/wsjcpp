#include "wsjcpp_arguments.h"
#include <wsjcpp_core.h>

WsjcppArgumentSingle::WsjcppArgumentSingle(const std::string &sName, const std::string &sDescription) {
    TAG = "WsjcppArgumentSingle-" + sName;
    m_sName = sName;
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentSingle::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentSingle::getDescription() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentSingle::help(const std::string &sProgramName, const std::string &sPrefix) {
    return sPrefix + "[" + m_sName + "] - " + m_sDescription;
}

// ---------------------------------------------------------------------

WsjcppArgumentParameter::WsjcppArgumentParameter(const std::string &sName, const std::string &sDescription) {
    TAG = "WsjcppArgumentParameter-" + sName;
    m_sName = sName;
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentParameter::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentParameter::getDescription() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentParameter::getValue() {
    return m_sValue;
}

// ---------------------------------------------------------------------

void WsjcppArgumentParameter::setValue(const std::string &sValue) {
    m_sValue = sValue;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentParameter::help(const std::string &sProgramName, const std::string &sPrefix) {
    return sPrefix + "[" + m_sName + " <val>] - " + m_sDescription;
}

// ---------------------------------------------------------------------

WsjcppArgumentProcessor::WsjcppArgumentProcessor(const std::vector<std::string> &vNames, const std::string &sDescription) {
    if (vNames.size() < 1) {
        WsjcppLog::throw_err(TAG, "Names must have 1 or more values for '" + sDescription + "'");
    }
    m_vNames = vNames;
    TAG = "WsjcppArgumentProcessor-" + this->getNamesAsString();
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------

const std::vector<std::string> &WsjcppArgumentProcessor::getNames() {
    return m_vNames;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentProcessor::getNamesAsString() {
    std::string sRet;
    for (int i = 0; i < m_vNames.size(); i++) {
        if (sRet.size() > 0) {
            sRet += "|";
        }
        sRet += m_vNames[i];
    }
    return sRet;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentProcessor::getDescription() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

void WsjcppArgumentProcessor::registryProcessor(WsjcppArgumentProcessor *p) {
    for (int i = 0; i < m_vNames.size(); i++) {
        std::string sName = m_vNames[i];
        if (hasRegisteredArgumentName(sName)) {
            WsjcppLog::throw_err(TAG, "Argument Name '" + sName + "' already registered");
        }
    }
    m_vProcessors.push_back(p);
}

// ---------------------------------------------------------------------

void WsjcppArgumentProcessor::registryExample(const std::string &sExample) {
    m_vExamples.push_back(sExample);
}

// ---------------------------------------------------------------------

void WsjcppArgumentProcessor::registrySingleArgument(const std::string &sArgumentName, const std::string &sDescription) {
    if (hasRegisteredArgumentName(sArgumentName)) {
        WsjcppLog::throw_err(TAG, "Argument Name '" + sArgumentName + "' already registered");
    }
    m_vSingleArguments.push_back(new WsjcppArgumentSingle(sArgumentName, sDescription));
}

// ---------------------------------------------------------------------

void WsjcppArgumentProcessor::registryParameterArgument(const std::string &sArgumentName, const std::string &sDescription) {
    if (hasRegisteredArgumentName(sArgumentName)) {
        WsjcppLog::throw_err(TAG, "Argument Name '" + sArgumentName + "' already registered");
    }
    m_vParameterArguments.push_back(new WsjcppArgumentParameter(sArgumentName, sDescription));
}

// ---------------------------------------------------------------------

WsjcppArgumentSingle *WsjcppArgumentProcessor::findRegisteredSingleArgument(const std::string &sArgumentName) {
    WsjcppArgumentSingle *pRet = nullptr;
    for (int i = 0; i < m_vSingleArguments.size(); i++) {
        if (m_vSingleArguments[i]->getName() == sArgumentName) {
            if (pRet == nullptr) {
                pRet = m_vSingleArguments[i];
            } else {
                WsjcppLog::throw_err(TAG, "Single argument '" + sArgumentName + "' already exists");
            }
        }
    }
    return pRet;
}

// ---------------------------------------------------------------------

WsjcppArgumentParameter *WsjcppArgumentProcessor::findRegisteredParameterArgument(const std::string &sArgumentName) {
    WsjcppArgumentParameter *pRet = nullptr;
    for (int i = 0; i < m_vParameterArguments.size(); i++) {
        if (m_vParameterArguments[i]->getName() == sArgumentName) {
            if (pRet == nullptr) {
                pRet = m_vParameterArguments[i];
            } else {
                WsjcppLog::throw_err(TAG, "Single argument '" + sArgumentName + "' already exists");
            }
        }
    }
    return pRet;
}


// ---------------------------------------------------------------------

WsjcppArgumentProcessor *WsjcppArgumentProcessor::findRegisteredProcessor(const std::string &sArgumentName) {
    WsjcppArgumentProcessor *pRet = nullptr;
    for (int i = 0; i < m_vProcessors.size(); i++) {
        std::vector<std::string> vNames = m_vProcessors[i]->getNames();
        for (int n = 0; n < vNames.size(); n++) {
            if (vNames[n] == sArgumentName) {
                if (pRet == nullptr) {
                    pRet = m_vProcessors[i];
                } else {
                    WsjcppLog::throw_err(TAG, "Several processors can handle this arguments");
                }
            }
        }
    }
    return pRet;
}

// ---------------------------------------------------------------------

bool WsjcppArgumentProcessor::hasRegisteredArgumentName(const std::string &sArgumentName) {
    for (int i = 0; i < m_vParameterArguments.size(); i++) {
        if (m_vParameterArguments[i]->getName() == sArgumentName) {
            return true;
        }
    }

    for (int i = 0; i < m_vProcessors.size(); i++) {
        std::vector<std::string> vNames = m_vProcessors[i]->getNames();
        for (int n = 0; n < vNames.size(); n++) {
            if (vNames[n] == sArgumentName) {
                return true;
            }
        }
        
    }

    for (int i = 0; i < m_vSingleArguments.size(); i++) {
        if (m_vSingleArguments[i]->getName() == sArgumentName) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppArgumentProcessor::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    WsjcppLog::throw_err(TAG, "No support single argument '" + sArgumentName + "'");
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppArgumentProcessor::applyParameterArgument(const std::string &sProgramName, const std::string &sArgumentName, const std::string &sValue) {
    WsjcppLog::throw_err(TAG, "No support parameter argument '" + sArgumentName + "' for '" + getNamesAsString() + "'");
    return false;
}

// ---------------------------------------------------------------------

int WsjcppArgumentProcessor::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppLog::throw_err(TAG, "Processor '" + getNamesAsString() + "' has not implementation");
    return -1;
}

// ---------------------------------------------------------------------

std::string WsjcppArgumentProcessor::help(const std::string &sProgramName, const std::string &sPrefix) {
    std::string sRet = "";
    int nParams = 0;
    if (m_vSingleArguments.size() > 0 || m_vParameterArguments.size()) {
        sRet += "\r\n" + sPrefix + "Arguments: \r\n";

        for (int i = 0; i < m_vSingleArguments.size(); i++) {
            sRet += m_vSingleArguments[i]->help(sProgramName, sPrefix + "  ") + " \r\n";
            nParams++;
        }

        for (int i = 0; i < m_vParameterArguments.size(); i++) {
            sRet += m_vParameterArguments[i]->help(sProgramName, sPrefix + "  ") + " \r\n";
            nParams++;
        }
    }

    if (m_vExamples.size() > 0) {
        for (int ei = 0; ei < m_vExamples.size(); ei++) {
            sRet += sPrefix + "      - example " + std::to_string(ei) + ": " + m_vExamples[ei] + "\r\n";
        }
        sRet += "\r\n";
    }

    if (m_vProcessors.size() > 0) {
        sRet += "\r\n" + sPrefix + "Commands: \r\n";
        for (int i = 0; i < m_vProcessors.size(); i++) {
            WsjcppArgumentProcessor *p = m_vProcessors[i];
            // TODO need a previous Processors

            std::string sRoute = sProgramName;
            if (nParams > 0) {
                sRoute += " <arguments>";
            }
            sRoute += " " + p->getNamesAsString();
            // TODO: <package-name>
            sRet += sPrefix + "   " + sRoute + " - " + p->getDescription() + "\r\n";
            sRet += p->help(sRoute, sPrefix + "   ");
        }
        sRet += "\r\n";
    }

    // sRet += "\r\n"; // TODO
    return sRet;
}

// ---------------------------------------------------------------------

WsjcppArguments::WsjcppArguments(int argc, const char* argv[], WsjcppArgumentProcessor *pRoot) {
    TAG = "WsjcppArguments";
    for (int i = 0; i < argc; i++) {
        m_vArguments.push_back(std::string(argv[i]));
    }
    m_sProgramName = m_vArguments[0];
    m_vArguments.erase(m_vArguments.begin());
    m_pRoot = pRoot;
}

// ---------------------------------------------------------------------

WsjcppArguments::~WsjcppArguments() {
    // TODO
}

// ---------------------------------------------------------------------

int WsjcppArguments::exec() {
    if (m_pRoot == nullptr) {
        WsjcppLog::throw_err(TAG, "Root could not be nullptr");
    }
    std::vector<std::string> vArgs(m_vArguments);
    return this->recursiveExec(m_pRoot, vArgs);
}

// ---------------------------------------------------------------------

int WsjcppArguments::recursiveExec(WsjcppArgumentProcessor *pArgumentProcessor, std::vector<std::string> &vSubArguments) {
    
    std::vector<WsjcppArgumentSingle *> vSingleArguments;
    std::vector<WsjcppArgumentParameter *> vParameterArguments;
    vSubArguments = extractSingleAndParameterArguments(pArgumentProcessor, vSubArguments, vSingleArguments, vParameterArguments);

    // apply single arguments
    for (int i = 0; i < vSingleArguments.size(); i++) {
        WsjcppArgumentSingle *p = vSingleArguments[i];
        if (!pArgumentProcessor->applySingleArgument(m_sProgramName, p->getName())) {
            WsjcppLog::err(TAG, "Could not apply single argument '" + p->getName() + "' ");
            return -1;
        }
    }

    // apply parameter arguments
    for (int i = 0; i < vParameterArguments.size(); i++) {
        WsjcppArgumentParameter *p = vParameterArguments[i];
        if (!pArgumentProcessor->applyParameterArgument(m_sProgramName, p->getName(), p->getValue())) {
            WsjcppLog::err(TAG, "Could not apply parameter argument '" + p->getName() + "' for '" + pArgumentProcessor->getNamesAsString() + "'");
            return -1;
        }
    }

    if (vSubArguments.size() > 0) {
        WsjcppArgumentProcessor *pNextProcessor = pArgumentProcessor->findRegisteredProcessor(vSubArguments[0]);
        if (pNextProcessor != nullptr) {
            vSubArguments.erase(vSubArguments.begin());
            return this->recursiveExec(pNextProcessor, vSubArguments);
        }
    }

    return pArgumentProcessor->exec(m_sProgramName, vSubArguments);
}

// ---------------------------------------------------------------------

std::vector<std::string> WsjcppArguments::extractSingleAndParameterArguments(
    WsjcppArgumentProcessor *pArgumentProcessor, 
    const std::vector<std::string> &vArguments,
    std::vector<WsjcppArgumentSingle *> &vSingleArguments,
    std::vector<WsjcppArgumentParameter *> &vParameterArguments
) {
    std::vector<std::string> vArgs(vArguments);
    bool bFound = true;
    while (bFound) {
        bFound = false;
        if (vArgs.size() > 0) {
            std::string sFirst = vArgs[0];
            WsjcppArgumentSingle *pSingle = pArgumentProcessor->findRegisteredSingleArgument(sFirst);
            WsjcppArgumentParameter *pParameter = pArgumentProcessor->findRegisteredParameterArgument(sFirst);
            if (pSingle != nullptr) {
                vArgs.erase(vArgs.begin());
                bFound = true;
                vSingleArguments.push_back(pSingle);
            } else if (pParameter != nullptr) {
                bFound = true;
                vParameterArguments.push_back(pParameter);
                vArgs.erase(vArgs.begin());
                if (vArgs.size() == 0) {
                    WsjcppLog::throw_err(TAG, "Expected value for '" + pParameter->getName() + "'");
                } else {
                    pParameter->setValue(vArgs[0]);
                    vArgs.erase(vArgs.begin());
                }
            }
        }
    }
    return vArgs;
}

// ---------------------------------------------------------------------

std::string WsjcppArguments::help() {
    std::string sRet = "\r\n";
    sRet += "Usage: " + m_sProgramName + " <arguments> [<command> <arguments>] ... [<subcommand> <arguments>]\r\n\r\n";
    sRet += "    " + m_pRoot->getDescription() + "\r\n";

    return sRet + m_pRoot->help(m_sProgramName, "  ");
}

// ---------------------------------------------------------------------

