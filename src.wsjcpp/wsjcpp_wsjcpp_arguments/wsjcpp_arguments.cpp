#include "wsjcpp_arguments.h"
#include <wsjcpp_core.h>

WSJCppArgumentSingle::WSJCppArgumentSingle(const std::string &sName, const std::string &sDescription) {
    TAG = "WSJCppArgumentSingle-" + sName;
    m_sName = sName;
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentSingle::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentSingle::getDescription() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentSingle::help(const std::string &sProgramName, const std::string &sPrefix) {
    return sPrefix + "[" + m_sName + "] - " + m_sDescription;
}

// ---------------------------------------------------------------------

WSJCppArgumentParameter::WSJCppArgumentParameter(const std::string &sName, const std::string &sDescription) {
    TAG = "WSJCppArgumentParameter-" + sName;
    m_sName = sName;
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentParameter::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentParameter::getDescription() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentParameter::getValue() {
    return m_sValue;
}

// ---------------------------------------------------------------------

void WSJCppArgumentParameter::setValue(const std::string &sValue) {
    m_sValue = sValue;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentParameter::help(const std::string &sProgramName, const std::string &sPrefix) {
    return sPrefix + "[" + m_sName + " <val>] - " + m_sDescription;
}

// ---------------------------------------------------------------------

WSJCppArgumentProcessor::WSJCppArgumentProcessor(const std::string &sName, const std::string &sDescription) {
    TAG = "WSJCppArgumentProcessor-" + sName;
    m_sName = sName;
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------

WSJCppArgumentProcessor::WSJCppArgumentProcessor(const std::vector<std::string> &vNames, const std::string &sDescription) {
    if (vNames.size() < 1) {
        WSJCppLog::throw_err(TAG, "Names must have 1 or more values for '" + sDescription + "'");
    }
    std::string sName = vNames[0];
    TAG = "WSJCppArgumentProcessor-" + sName;
    m_sName = sName;
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentProcessor::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentProcessor::getDescription() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

void WSJCppArgumentProcessor::registryProcessor(WSJCppArgumentProcessor *p) {
    if (hasRegisteredArgumentName(p->getName())) {
        WSJCppLog::throw_err(TAG, "Argument Name '" + p->getName() + "' already registered");
    }
    m_vProcessors.push_back(p);
}

// ---------------------------------------------------------------------

void WSJCppArgumentProcessor::registryExample(const std::string &sExample) {
    m_vExamples.push_back(sExample);
}

// ---------------------------------------------------------------------

void WSJCppArgumentProcessor::registrySingleArgument(const std::string &sArgumentName, const std::string &sDescription) {
    if (hasRegisteredArgumentName(sArgumentName)) {
        WSJCppLog::throw_err(TAG, "Argument Name '" + sArgumentName + "' already registered");
    }
    m_vSingleArguments.push_back(new WSJCppArgumentSingle(sArgumentName, sDescription));
}

// ---------------------------------------------------------------------

void WSJCppArgumentProcessor::registryParameterArgument(const std::string &sArgumentName, const std::string &sDescription) {
    if (hasRegisteredArgumentName(sArgumentName)) {
        WSJCppLog::throw_err(TAG, "Argument Name '" + sArgumentName + "' already registered");
    }
    m_vParameterArguments.push_back(new WSJCppArgumentParameter(sArgumentName, sDescription));
}

// ---------------------------------------------------------------------

WSJCppArgumentSingle *WSJCppArgumentProcessor::findRegisteredSingleArgument(const std::string &sArgumentName) {
    WSJCppArgumentSingle *pRet = nullptr;
    for (int i = 0; i < m_vSingleArguments.size(); i++) {
        if (m_vSingleArguments[i]->getName() == sArgumentName) {
            if (pRet == nullptr) {
                pRet = m_vSingleArguments[i];
            } else {
                WSJCppLog::throw_err(TAG, "Single argument '" + sArgumentName + "' already exists");
            }
        }
    }
    return pRet;
}

// ---------------------------------------------------------------------

WSJCppArgumentParameter *WSJCppArgumentProcessor::findRegisteredParameterArgument(const std::string &sArgumentName) {
    WSJCppArgumentParameter *pRet = nullptr;
    for (int i = 0; i < m_vParameterArguments.size(); i++) {
        if (m_vParameterArguments[i]->getName() == sArgumentName) {
            if (pRet == nullptr) {
                pRet = m_vParameterArguments[i];
            } else {
                WSJCppLog::throw_err(TAG, "Single argument '" + sArgumentName + "' already exists");
            }
        }
    }
    return pRet;
}


// ---------------------------------------------------------------------

WSJCppArgumentProcessor *WSJCppArgumentProcessor::findRegisteredProcessor(const std::string &sArgumentName) {
    WSJCppArgumentProcessor *pRet = nullptr;
    for (int i = 0; i < m_vProcessors.size(); i++) {
        if (m_vProcessors[i]->getName() == sArgumentName) {
            if (pRet == nullptr) {
                pRet = m_vProcessors[i];
            } else {
                WSJCppLog::throw_err(TAG, "Several processors can handle this arguments");
            }
        }
    }
    return pRet;
}

// ---------------------------------------------------------------------

bool WSJCppArgumentProcessor::hasRegisteredArgumentName(const std::string &sArgumentName) {
    for (int i = 0; i < m_vParameterArguments.size(); i++) {
        if (m_vParameterArguments[i]->getName() == sArgumentName) {
            return true;
        }
    }

    for (int i = 0; i < m_vProcessors.size(); i++) {
        if (m_vProcessors[i]->getName() == sArgumentName) {
            return true;
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

bool WSJCppArgumentProcessor::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    WSJCppLog::throw_err(TAG, "No support single argument '" + sArgumentName + "'");
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppArgumentProcessor::applyParameterArgument(const std::string &sProgramName, const std::string &sArgumentName, const std::string &sValue) {
    WSJCppLog::throw_err(TAG, "No support parameter argument '" + sArgumentName + "' for '" + getName() + "'");
    return false;
}

// ---------------------------------------------------------------------

int WSJCppArgumentProcessor::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppLog::throw_err(TAG, "Processor '" + getName() + "' has not implementation");
    return -1;
}

// ---------------------------------------------------------------------

std::string WSJCppArgumentProcessor::help(const std::string &sProgramName, const std::string &sPrefix) {
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
            WSJCppArgumentProcessor *p = m_vProcessors[i];
            // TODO need a previous Processors

            std::string sRoute = sProgramName;
            if (nParams > 0) {
                sRoute += " <arguments>";
            }
            sRoute += " " + p->getName();
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

WSJCppArguments::WSJCppArguments(int argc, const char* argv[], WSJCppArgumentProcessor *pRoot) {
    TAG = "WSJCppArguments";
    for (int i = 0; i < argc; i++) {
        m_vArguments.push_back(std::string(argv[i]));
    }
    m_sProgramName = m_vArguments[0];
    m_vArguments.erase(m_vArguments.begin());
    m_pRoot = pRoot;
}

// ---------------------------------------------------------------------

int WSJCppArguments::exec() {
    if (m_pRoot == nullptr) {
        WSJCppLog::throw_err(TAG, "Root could not be nullptr");
    }
    std::vector<std::string> vArgs(m_vArguments);
    return this->recursiveExec(m_pRoot, vArgs);
}

// ---------------------------------------------------------------------

int WSJCppArguments::recursiveExec(WSJCppArgumentProcessor *pArgumentProcessor, std::vector<std::string> &vSubArguments) {
    
    std::vector<WSJCppArgumentSingle *> vSingleArguments;
    std::vector<WSJCppArgumentParameter *> vParameterArguments;
    vSubArguments = extractSingleAndParameterArguments(pArgumentProcessor, vSubArguments, vSingleArguments, vParameterArguments);

    // apply single arguments
    for (int i = 0; i < vSingleArguments.size(); i++) {
        WSJCppArgumentSingle *p = vSingleArguments[i];
        if (!pArgumentProcessor->applySingleArgument(m_sProgramName, p->getName())) {
            WSJCppLog::err(TAG, "Could not apply single argument '" + p->getName() + "' ");
            return -1;
        }
    }

    // apply parameter arguments
    for (int i = 0; i < vParameterArguments.size(); i++) {
        WSJCppArgumentParameter *p = vParameterArguments[i];
        if (!pArgumentProcessor->applyParameterArgument(m_sProgramName, p->getName(), p->getValue())) {
            WSJCppLog::err(TAG, "Could not apply parameter argument '" + p->getName() + "' for '" + pArgumentProcessor->getName() + "'");
            return -1;
        }
    }

    if (vSubArguments.size() > 0) {
        WSJCppArgumentProcessor *pNextProcessor = pArgumentProcessor->findRegisteredProcessor(vSubArguments[0]);
        if (pNextProcessor != nullptr) {
            vSubArguments.erase(vSubArguments.begin());
            return this->recursiveExec(pNextProcessor, vSubArguments);
        }
    }

    return pArgumentProcessor->exec(m_sProgramName, vSubArguments);
}

// ---------------------------------------------------------------------

std::vector<std::string> WSJCppArguments::extractSingleAndParameterArguments(
    WSJCppArgumentProcessor *pArgumentProcessor, 
    const std::vector<std::string> &vArguments,
    std::vector<WSJCppArgumentSingle *> &vSingleArguments,
    std::vector<WSJCppArgumentParameter *> &vParameterArguments
) {
    std::vector<std::string> vArgs(vArguments);
    bool bFound = true;
    while (bFound) {
        bFound = false;
        if (vArgs.size() > 0) {
            std::string sFirst = vArgs[0];
            WSJCppArgumentSingle *pSingle = pArgumentProcessor->findRegisteredSingleArgument(sFirst);
            WSJCppArgumentParameter *pParameter = pArgumentProcessor->findRegisteredParameterArgument(sFirst);
            if (pSingle != nullptr) {
                vArgs.erase(vArgs.begin());
                bFound = true;
                vSingleArguments.push_back(pSingle);
            } else if (pParameter != nullptr) {
                bFound = true;
                vParameterArguments.push_back(pParameter);
                vArgs.erase(vArgs.begin());
                if (vArgs.size() == 0) {
                    WSJCppLog::throw_err(TAG, "Expected value for '" + pParameter->getName() + "'");
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

std::string WSJCppArguments::help() {
    std::string sRet = "\r\n";
    sRet += "Usage: " + m_sProgramName + " <arguments> [<command> <arguments>] ... [<subcommand> <arguments>]\r\n\r\n";
    sRet += "    " + m_pRoot->getDescription() + "\r\n";

    return sRet + m_pRoot->help(m_sProgramName, "  ");
}

// ---------------------------------------------------------------------


