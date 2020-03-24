#include "wsjcpp_safe_scripting.h"
#include <unistd.h>
#include <string.h>
#include <wsjcpp_core.h>
#include <algorithm>
// #include <wsjcpp_safe_scripting_proc_make_dir.h>

// ---------------------------------------------------------------------
// WSJCppSafeScriptingVariable

WSJCppSafeScriptingVariable::WSJCppSafeScriptingVariable(const std::string &sValue) {
    TAG = "WSJCppSafeScriptingVariable";
    m_sValue = sValue;
}

// ---------------------------------------------------------------------

std::string WSJCppSafeScriptingVariable::getValue() {
    return m_sValue;
}

// ---------------------------------------------------------------------

void WSJCppSafeScriptingVariable::setValue(const std::string &sValue) {
    m_sValue = sValue;
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingProc

WSJCppSafeScriptingProc::WSJCppSafeScriptingProc(const std::string &sProcName) {
    TAG = "WSJCppSafeScriptingProc[" + sProcName + "]";
    m_sProcName = sProcName;
}

// ---------------------------------------------------------------------

std::string WSJCppSafeScriptingProc::getName() {
    return m_sProcName;
}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProc::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    WSJCppLog::err(TAG, "Procedure not implemented");
    return false;
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcLogInfo

WSJCppSafeScriptingProcLogInfo::WSJCppSafeScriptingProcLogInfo() 
: WSJCppSafeScriptingProc("log_info") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcLogInfo::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    std::string sRet = "";
    for (int i = 0; i < vArgs.size(); i++) {
        sRet += vArgs[i]->getValue();
    }
    WSJCppLog::info(TAG, sRet);
    return true;
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcedureSetValue

WSJCppSafeScriptingProcedureSetValue::WSJCppSafeScriptingProcedureSetValue() 
: WSJCppSafeScriptingProc("set_value") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcedureSetValue::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    std::string sRet = "";
    if (vArgs.size() != 2) {
        WSJCppLog::err(TAG, "Expected 2 arguments");
        return false;
    }
    vArgs[0]->setValue(vArgs[1]->getValue());
    return true;
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcedureConcat

WSJCppSafeScriptingProcedureConcat::WSJCppSafeScriptingProcedureConcat() 
: WSJCppSafeScriptingProc("concat") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcedureConcat::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    std::string sRet = "";
    if (vArgs.size() < 2) {
        WSJCppLog::err(TAG, "Expected 2 and more variables");
        return false;
    }
    std::string sNewValue = "";
    for (int i = 0; i < vArgs.size(); i++) {
        sNewValue += vArgs[i]->getValue();
    }
    vArgs[0]->setValue(sNewValue);
    return true;
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcMakeDir

WSJCppSafeScriptingProcMakeDir::WSJCppSafeScriptingProcMakeDir() 
: WSJCppSafeScriptingProc("make_dir") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcMakeDir::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    std::string sRet = "";
    if (vArgs.size() != 1) {
        WSJCppLog::err(TAG, "Expected 1 arguments");
        return false;
    }
    // TODO check rootdir safe!
    std::string sDir = vArgs[0]->getValue();
    if (WSJCppCore::dirExists(sDir)) {
        return true;
    }
    return WSJCppCore::makeDir(sDir);
}


// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcNormalizeClassName

WSJCppSafeScriptingProcNormalizeClassName::WSJCppSafeScriptingProcNormalizeClassName() 
: WSJCppSafeScriptingProc("normalize_class_name") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcNormalizeClassName::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 1) {
        WSJCppLog::err(TAG, "Expected 1 arguments");
        return false;
    }

    std::string sInput = vArgs[0]->getValue();;
    std::string sRet = ""; 
    for (int i = 0; i < sInput.size(); i++) {
        char c = sInput[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            sRet += c;
        }
    }
    if (sRet != sInput) {
        WSJCppLog::info(TAG, "normalized class name '" + sInput + "' -> '" + sRet + "'");
    }
    vArgs[0]->setValue(sRet);
    return true;
}


// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcCamelCaseToSnakeCase

WSJCppSafeScriptingProcCamelCaseToSnakeCase::WSJCppSafeScriptingProcCamelCaseToSnakeCase() 
: WSJCppSafeScriptingProc("convert_CamelCase_to_snake_case") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcCamelCaseToSnakeCase::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 2) {
        WSJCppLog::err(TAG, "Expected 2 arguments");
        return false;
    }
    std::string sInput = vArgs[0]->getValue();
    std::string sRet = "";
    for (int i = 0; i < sInput.size(); i++) {
        char c = sInput[i];
        if (c >= 'A' && c <= 'Z') {
            c = char(c + 32);
            sRet += sRet.length() == 0 ? "" : "_";
            sRet += c;
        } else if (c >= 'a' && c <= 'z') {
            sRet += c;
        } else if (c >= '0' && c <= '9') {
            sRet += c;
        } else {
            WSJCppLog::warn(TAG, std::string("Ignored ") + c);
        }
    }
    vArgs[1]->setValue(sRet);
    return true;
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcToUpperCase

WSJCppSafeScriptingProcToUpperCase::WSJCppSafeScriptingProcToUpperCase() 
: WSJCppSafeScriptingProc("to_upper_case") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcToUpperCase::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 1) {
        WSJCppLog::err(TAG, "Expected 1 arguments");
        return false;
    }
    std::string sInput = vArgs[0]->getValue();
    std::string sRet = WSJCppCore::toUpper(sInput);
    vArgs[0]->setValue(sRet);
    return true;
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcWriteFile

WSJCppSafeScriptingProcWriteFile::WSJCppSafeScriptingProcWriteFile() 
: WSJCppSafeScriptingProc("write_file") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcWriteFile::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 2) {
        WSJCppLog::err(TAG, "Expected 2 arguments");
        return false;
    }
    std::string sFilePath = vArgs[0]->getValue();
    // TODO check safe file
    std::string sFileContent = vArgs[1]->getValue();
    return WSJCppCore::writeFile(sFilePath, sFileContent);
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingProcCMakeListsTxtAppendWSJCpp

WSJCppSafeScriptingProcCMakeListsTxtAppendWSJCpp::WSJCppSafeScriptingProcCMakeListsTxtAppendWSJCpp() 
: WSJCppSafeScriptingProc("cmakelists_txt_append_wsjcpp") {

}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingProcCMakeListsTxtAppendWSJCpp::exec(const std::vector<WSJCppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 1) {
        WSJCppLog::err(TAG, "Expected 1 arguments");
        return false;
    }
    std::string sFilePath = vArgs[0]->getValue();
    std::string sToAppend = "list (APPEND WSJCPP_SOURCES \"" + sFilePath + "\")";
    std::string sCMakeListsTxt;
    if (!WSJCppCore::readTextFile("./CMakeLists.txt", sCMakeListsTxt)) {
        WSJCppLog::err(TAG, "Could not read file ./CMakeLists.txt");
        return false;
    }
    WSJCppCore::trim(sCMakeListsTxt);

    std::string sCMakeListsTxtOutput;
    std::vector<std::string> vLines = WSJCppCore::split(sCMakeListsTxt, "\n");
    bool bAdded = false;
    int nState = 0;
    for (int i = 0; i < vLines.size(); i++) {
        std::string sLine = vLines[i];
        WSJCppCore::trim(sLine);
        if (nState == 0 && sLine == "#### BEGIN_WSJCPP_APPEND") {
            nState = 1;
        } else if (nState == 1) {
            if (sLine == sToAppend) {
                bAdded = true; // already added 
            }
        } if (nState == 1 && sLine == "#### END_WSJCPP_APPEND") {
            if (!bAdded) {
                sCMakeListsTxtOutput += "list (APPEND WSJCPP_SOURCES \"" + sFilePath + "\")\n";
                bAdded = true;
            }
            nState = 0;
        }
        sCMakeListsTxtOutput += vLines[i] + "\n";
    }
    sCMakeListsTxtOutput += "\n";
    if (!bAdded) {
        WSJCppLog::err(TAG, "Not found '#### BEGIN_WSJCPP_APPEND' and '#### END_WSJCPP_APPEND' in file './CMakeLists.txt'");
        return false;
    }
    return WSJCppCore::writeFile("./CMakeLists.txt", sCMakeListsTxtOutput);
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingToken

WSJCppSafeScriptingToken::WSJCppSafeScriptingToken(
    const std::string &sToken,
    const std::string &sScriptName,
    int nNumberOfLine
) {
    m_sToken = sToken;
    m_sScriptName = sScriptName;
    m_nNumberOfLine = nNumberOfLine;
}

// ---------------------------------------------------------------------

std::string WSJCppSafeScriptingToken::getToken() {
    if (!this->hasString()) {
        return m_sToken;
    }
    std::string sRet = m_sToken.substr(1, m_sToken.length() - 2);
    return sRet;
}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingToken::hasString() {
    return m_sToken.length() > 0 && m_sToken[0] == '"' && m_sToken[m_sToken.length()-1] == '"';
}

// ---------------------------------------------------------------------

std::string WSJCppSafeScriptingToken::getContextForLog() {
    return m_sScriptName + ":" + std::to_string(m_nNumberOfLine) + " -> " + m_sToken;
}

// ---------------------------------------------------------------------
// WSJCppSafeScriptingContext

WSJCppSafeScriptingContext::WSJCppSafeScriptingContext() {
    TAG = "WSJCppSafeScriptingContext";
    addProc(new WSJCppSafeScriptingProcLogInfo());
    addProc(new WSJCppSafeScriptingProcedureSetValue());
    addProc(new WSJCppSafeScriptingProcedureConcat());
    addProc(new WSJCppSafeScriptingProcMakeDir());
    addProc(new WSJCppSafeScriptingProcNormalizeClassName());
    addProc(new WSJCppSafeScriptingProcCamelCaseToSnakeCase());
    addProc(new WSJCppSafeScriptingProcToUpperCase());
    addProc(new WSJCppSafeScriptingProcWriteFile());
    addProc(new WSJCppSafeScriptingProcCMakeListsTxtAppendWSJCpp());
}

// ---------------------------------------------------------------------

WSJCppSafeScriptingContext::~WSJCppSafeScriptingContext() {
    // TODO cleanup all pointers
    WSJCppLog::warn(TAG, "TODO cleanup all pointers");
}

// ---------------------------------------------------------------------

WSJCppSafeScriptingVariable * WSJCppSafeScriptingContext::addVariable(const std::string &sName) {
    if (hasVariable(sName)) {
        WSJCppLog::err(TAG, "Variable '" + sName + "' already defined");
        return nullptr;
    }
    WSJCppSafeScriptingVariable *pVar = new WSJCppSafeScriptingVariable("");
    m_vVariables[sName] = pVar;
    return pVar;
}

// ---------------------------------------------------------------------

WSJCppSafeScriptingVariable * WSJCppSafeScriptingContext::getVariable(const std::string &sName) {
    std::map<std::string, WSJCppSafeScriptingVariable *>::iterator it;
    it = m_vVariables.find(sName);
    if (it != m_vVariables.end()) {
        return it->second;
    }
    return nullptr;
}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingContext::hasVariable(const std::string &sName) {
    return this->hasVar(sName);
}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingContext::hasVar(const std::string &sName) {
    return m_vVariables.find(sName) != m_vVariables.end();
}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingContext::addProc(WSJCppSafeScriptingProc *pProc) {
    if (this->hasProc(pProc->getName())) {
        WSJCppLog::err(TAG, "Proc already defined '" + pProc->getName() + "'");
        return false;
    }
    m_vProcs[pProc->getName()] = pProc;
    return true;
}

// ---------------------------------------------------------------------

WSJCppSafeScriptingProc *WSJCppSafeScriptingContext::getProc(const std::string &sName) {
    std::map<std::string, WSJCppSafeScriptingProc *>::iterator it;
    it = m_vProcs.find(sName);
    if (it != m_vProcs.end()) {
        return it->second;
    }
    return nullptr;
}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingContext::hasProc(const std::string &sName) {
    return m_vProcs.find(sName) != m_vProcs.end();
}

// ---------------------------------------------------------------------

int WSJCppSafeScriptingContext::exec(
    const std::string &sScriptRootDir,
    const std::string &sScriptFileName, 
    const std::string &sScriptContent, 
    std::vector<std::string> vArgs
) {
    m_sScriptRootDir = sScriptRootDir;
    m_sScriptFileName = sScriptFileName;
    m_sScriptContent = sScriptContent;

    m_vVariables["rootdir"] = new WSJCppSafeScriptingVariable(m_sScriptRootDir);
    m_vVariables["script_filename"] = new WSJCppSafeScriptingVariable(m_sScriptFileName);
    for (int i = 0; i < vArgs.size(); i++) {
        std::string sArgName = "arg" + std::to_string(i+1);
        WSJCppLog::info(TAG, sArgName + " = '" + vArgs[i] + "'");
        m_vVariables[sArgName] = new WSJCppSafeScriptingVariable(vArgs[i]);
    }
    if (!parseScript()) {
        WSJCppLog::err(TAG, "Parse script failed");
        return -1;
    }
    std::string sError = "";
    for (int i = 0; i < m_vScriptTokens.size(); i++) {
        WSJCppSafeScriptingToken *pToken = m_vScriptTokens[i];
        std::string sToken = pToken->getToken();
        if (sToken == "error") {
            WSJCppLog::err(TAG, "error");
            return -1;
        } else if (sToken == "exit") {
            return 0;
        } else if (sToken == "var") {
            std::string sVarName = m_vScriptTokens[i+1]->getToken();
            i++;
            std::string sEndToken = m_vScriptTokens[i+1]->getToken();
            if (sEndToken != "end") {
                WSJCppLog::err(TAG, "Expected token 'end' after '" + sVarName + "' but got '" + sEndToken + "'");
                return -1;
            }
            i++;
            // TODO check empty name
            if (hasVariable(sVarName)) {
                WSJCppLog::err(TAG, "variable already defined " + sVarName);
                return -1;
            } else if (hasProc(sVarName)) {
                WSJCppLog::err(TAG, "Procedure with this name already exists " + sVarName);
                return -1;
            } else {
                addVariable(sVarName); // TODO add variable
            }
        } else if (hasProc(sToken)) {
            std::vector<WSJCppSafeScriptingVariable *> vArgs;
            std::vector<WSJCppSafeScriptingVariable *> vRuntimeRemoveAfter;
            std::vector<WSJCppSafeScriptingToken *> vTokenArgs;
            for (int n = i+1; n < m_vScriptTokens.size(); n++) {
                WSJCppSafeScriptingToken *pToken2 = m_vScriptTokens[n];
                std::string sTokenValue2 = pToken2->getToken();
                vTokenArgs.push_back(pToken2);
                if (sTokenValue2 == "end") {
                    i = n;
                    vTokenArgs.pop_back();
                    break;
                } else if (pToken2->hasString()) {
                    WSJCppSafeScriptingVariable *pVar = addVariable("vartmp_" + WSJCppCore::createUuid());
                    pVar->setValue(sTokenValue2);
                    vArgs.push_back(pVar);
                    vRuntimeRemoveAfter.push_back(pVar);
                } else if (hasVariable(sTokenValue2)) {
                    WSJCppSafeScriptingVariable *pVar = getVariable(sTokenValue2);
                    vArgs.push_back(pVar);
                } else {
                    WSJCppLog::err(TAG, "Uknown token: " + sTokenValue2);
                    // TODO cleanup 
                    return -1;
                }
            }
            WSJCppSafeScriptingProc *pProcedure = this->getProc(sToken);
            if (!pProcedure->exec(vArgs)) {
                std::string sDebugInfo = "Procedure: " + sToken + "\n";
                sDebugInfo += "Arguments: \n";
                for (int n = 0; n < vArgs.size(); n++) {
                    sDebugInfo += "   - " + vArgs[n]->getValue() + "\n";
                }
                sDebugInfo += "Tokens info:\n";
                sDebugInfo += pToken->getContextForLog() + "\n";
                for (int n = 0; n < vTokenArgs.size(); n++) {
                    sDebugInfo += vTokenArgs[n]->getContextForLog() + "\n";
                }
                WSJCppLog::err(TAG, sDebugInfo);
                return -1;
            };
            for (int n = 0; n < vRuntimeRemoveAfter.size(); n++) {
                delete vRuntimeRemoveAfter[n]; // TODO check
                vRuntimeRemoveAfter[n] = nullptr;
            }
            vRuntimeRemoveAfter.clear();
        } else {
            WSJCppLog::err(TAG, "Unknown token '" + sToken + "'  \n(" + pToken->getContextForLog() + ")");
            return -1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------

bool WSJCppSafeScriptingContext::parseScript() {
    m_vScriptTokens.clear();
    int n = 0;
    std::string sToken = "";
    int nLine = 0;
    for (int i = 0; i < m_sScriptContent.size(); i++) {
        char c = m_sScriptContent[i];
        if (n == 0 && c == '#') { // comment
            n = 2; // skip all
        } else if (n == 0 && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')) {
            n = 1;
            sToken = "";
            sToken += c;
        } else if (n == 0 && c == ' ') {
            // skip
        } else if (n == 0 && ((c >= '0' && c <= '9'))) {
            n = 4;
            sToken = "";
            sToken += c;
        } else if (n == 1 && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')) {
            sToken += c;
        } else if (n == 1 && (c == ' ' || c == '\n')) {
            m_vScriptTokens.push_back(new WSJCppSafeScriptingToken(sToken, m_sScriptFileName, nLine));
            // WSJCppLog::info(TAG, "Token '" + sToken + "'");
            if (c == '\n') {
                m_vScriptTokens.push_back(new WSJCppSafeScriptingToken("end", m_sScriptFileName, nLine));
                nLine++;
            }
            n = 0;
        }  else if (n == 0 && c == '"') {
            n = 10;
            sToken = "";
            sToken += c;
        } else if (n == 10 && c == '\\') {
            n = 11;
        } else if (n == 11 && c == 'n') {
            sToken += "\n";
            n = 10;
            nLine++;
        } else if (n == 11 && c == '\\') {
            sToken += '\\';
            n = 10;
        } else if (n == 11 && c == 't') {
            sToken += "\t";
            n = 10;
        } else if (n == 11 && c == '"') {
            sToken += "\"";
            n = 10;
        } else if (n == 11) {
            sToken += "\\";
            sToken += c;
            n = 10;
        } else if (n == 10 && c == '"') {
            sToken += c;
            n = 0;
            m_vScriptTokens.push_back(new WSJCppSafeScriptingToken(sToken, m_sScriptFileName, nLine));
        } else if (n == 10) {
            sToken += c;
        } else if (c == '\n') {
            int nSize = m_vScriptTokens.size();
            if (nSize > 0 && m_vScriptTokens[nSize-1]->getToken() != "end") {
                m_vScriptTokens.push_back(new WSJCppSafeScriptingToken("end", m_sScriptFileName, nLine));
            }
            n = 0;
            nLine++;
        } else if (n == 2) {
            // just skip
        } else {
            std::string sError = "parseScript, Unknown token '";
            sError += c;
            sError += "' in a line: " + m_sScriptFileName + ":" + std::to_string(nLine);
            WSJCppLog::err(TAG, sError);
            return false;
        }
    }
    if (n == 1) {
        m_vScriptTokens.push_back(new WSJCppSafeScriptingToken(sToken, m_sScriptFileName, nLine));
        m_vScriptTokens.push_back(new WSJCppSafeScriptingToken("end", m_sScriptFileName, nLine));
        // WSJCppLog::info(TAG, "parseScript, Last Token '" + sToken + "'");
    }
    return true;
}