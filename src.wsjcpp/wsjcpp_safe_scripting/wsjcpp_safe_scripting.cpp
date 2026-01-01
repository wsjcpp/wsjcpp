#include "wsjcpp_safe_scripting.h"
#include <unistd.h>
#include <string.h>
#include <wsjcpp_core.h>
#include <algorithm>
// #include <wsjcpp_safe_scripting_proc_make_dir.h>

// ---------------------------------------------------------------------
// WsjcppSafeScriptingVariable

WsjcppSafeScriptingVariable::WsjcppSafeScriptingVariable(const std::string &sValue) {
    TAG = "WsjcppSafeScriptingVariable";
    m_sValue = sValue;
}

// ---------------------------------------------------------------------

std::string WsjcppSafeScriptingVariable::getValue() {
    return m_sValue;
}

// ---------------------------------------------------------------------

void WsjcppSafeScriptingVariable::setValue(const std::string &sValue) {
    m_sValue = sValue;
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingProc

WsjcppSafeScriptingProc::WsjcppSafeScriptingProc(const std::string &sProcName) {
    TAG = "WsjcppSafeScriptingProc[" + sProcName + "]";
    m_sProcName = sProcName;
}

// ---------------------------------------------------------------------

std::string WsjcppSafeScriptingProc::getName() {
    return m_sProcName;
}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProc::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    WsjcppLog::err(TAG, "Procedure not implemented");
    return false;
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingProcLogInfo

WsjcppSafeScriptingProcLogInfo::WsjcppSafeScriptingProcLogInfo() 
: WsjcppSafeScriptingProc("log_info") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcLogInfo::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    std::string sRet = "";
    for (int i = 0; i < vArgs.size(); i++) {
        sRet += vArgs[i]->getValue();
    }
    WsjcppLog::info(TAG, sRet);
    return true;
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingProcedureSetValue

WsjcppSafeScriptingProcedureSetValue::WsjcppSafeScriptingProcedureSetValue() 
: WsjcppSafeScriptingProc("set_value") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcedureSetValue::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    std::string sRet = "";
    if (vArgs.size() != 2) {
        WsjcppLog::err(TAG, "Expected 2 arguments");
        return false;
    }
    vArgs[0]->setValue(vArgs[1]->getValue());
    return true;
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingProcedureConcat

WsjcppSafeScriptingProcedureConcat::WsjcppSafeScriptingProcedureConcat() 
: WsjcppSafeScriptingProc("concat") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcedureConcat::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    std::string sRet = "";
    if (vArgs.size() < 2) {
        WsjcppLog::err(TAG, "Expected 2 and more variables");
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
// WsjcppSafeScriptingProcMakeDir

WsjcppSafeScriptingProcMakeDir::WsjcppSafeScriptingProcMakeDir() 
: WsjcppSafeScriptingProc("make_dir") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcMakeDir::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    std::string sRet = "";
    if (vArgs.size() != 1) {
        WsjcppLog::err(TAG, "Expected 1 arguments");
        return false;
    }
    // TODO check rootdir safe!
    std::string sDir = vArgs[0]->getValue();
    if (WsjcppCore::dirExists(sDir)) {
        return true;
    }
    return WsjcppCore::makeDir(sDir);
}


// ---------------------------------------------------------------------
// WsjcppSafeScriptingProcNormalizeClassName

WsjcppSafeScriptingProcNormalizeClassName::WsjcppSafeScriptingProcNormalizeClassName() 
: WsjcppSafeScriptingProc("normalize_class_name") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcNormalizeClassName::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 1) {
        WsjcppLog::err(TAG, "Expected 1 arguments");
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
        WsjcppLog::info(TAG, "normalized class name '" + sInput + "' -> '" + sRet + "'");
    }
    vArgs[0]->setValue(sRet);
    return true;
}


// ---------------------------------------------------------------------
// WsjcppSafeScriptingProcCamelCaseToSnakeCase

WsjcppSafeScriptingProcCamelCaseToSnakeCase::WsjcppSafeScriptingProcCamelCaseToSnakeCase() 
: WsjcppSafeScriptingProc("convert_CamelCase_to_snake_case") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcCamelCaseToSnakeCase::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 2) {
        WsjcppLog::err(TAG, "Expected 2 arguments");
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
            WsjcppLog::warn(TAG, std::string("Ignored ") + c);
        }
    }
    vArgs[1]->setValue(sRet);
    return true;
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingProcToUpperCase

WsjcppSafeScriptingProcToUpperCase::WsjcppSafeScriptingProcToUpperCase() 
: WsjcppSafeScriptingProc("to_upper_case") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcToUpperCase::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 1) {
        WsjcppLog::err(TAG, "Expected 1 arguments");
        return false;
    }
    std::string sInput = vArgs[0]->getValue();
    std::string sRet = WsjcppCore::toUpper(sInput);
    vArgs[0]->setValue(sRet);
    return true;
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingProcWriteFile

WsjcppSafeScriptingProcWriteFile::WsjcppSafeScriptingProcWriteFile() 
: WsjcppSafeScriptingProc("write_file") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcWriteFile::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 2) {
        WsjcppLog::err(TAG, "Expected 2 arguments");
        return false;
    }
    std::string sFilePath = vArgs[0]->getValue();
    // TODO check safe file
    std::string sFileContent = vArgs[1]->getValue();
    return WsjcppCore::writeFile(sFilePath, sFileContent);
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingProcCMakeListsTxtAppendWsjcpp

WsjcppSafeScriptingProcCMakeListsTxtAppendWsjcpp::WsjcppSafeScriptingProcCMakeListsTxtAppendWsjcpp() 
: WsjcppSafeScriptingProc("cmakelists_txt_append_wsjcpp") {

}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingProcCMakeListsTxtAppendWsjcpp::exec(const std::vector<WsjcppSafeScriptingVariable *> &vArgs) {
    if (vArgs.size() != 1) {
        WsjcppLog::err(TAG, "Expected 1 arguments");
        return false;
    }
    std::string sFilePath = vArgs[0]->getValue();
    std::string sToAppend = "list (APPEND WSJCPP_SOURCES \"" + sFilePath + "\")";
    std::string sCMakeListsTxt;
    if (!WsjcppCore::readTextFile("./CMakeLists.txt", sCMakeListsTxt)) {
        WsjcppLog::err(TAG, "Could not read file ./CMakeLists.txt");
        return false;
    }
    WsjcppCore::trim(sCMakeListsTxt);

    std::string sCMakeListsTxtOutput;
    std::vector<std::string> vLines = WsjcppCore::split(sCMakeListsTxt, "\n");
    bool bAdded = false;
    int nState = 0;
    for (int i = 0; i < vLines.size(); i++) {
        std::string sLine = vLines[i];
        WsjcppCore::trim(sLine);
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
        WsjcppLog::err(TAG, "Not found '#### BEGIN_WSJCPP_APPEND' and '#### END_WSJCPP_APPEND' in file './CMakeLists.txt'");
        return false;
    }
    return WsjcppCore::writeFile("./CMakeLists.txt", sCMakeListsTxtOutput);
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingToken

WsjcppSafeScriptingToken::WsjcppSafeScriptingToken(
    const std::string &sToken,
    const std::string &sScriptName,
    int nNumberOfLine
) {
    m_sToken = sToken;
    m_sScriptName = sScriptName;
    m_nNumberOfLine = nNumberOfLine;
}

// ---------------------------------------------------------------------

std::string WsjcppSafeScriptingToken::getToken() {
    if (!this->hasString()) {
        return m_sToken;
    }
    std::string sRet = m_sToken.substr(1, m_sToken.length() - 2);
    return sRet;
}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingToken::hasString() {
    return m_sToken.length() > 0 && m_sToken[0] == '"' && m_sToken[m_sToken.length()-1] == '"';
}

// ---------------------------------------------------------------------

std::string WsjcppSafeScriptingToken::getContextForLog() {
    return m_sScriptName + ":" + std::to_string(m_nNumberOfLine) + " -> " + m_sToken;
}

// ---------------------------------------------------------------------
// WsjcppSafeScriptingContext

WsjcppSafeScriptingContext::WsjcppSafeScriptingContext() {
    TAG = "WsjcppSafeScriptingContext";
    addProc(new WsjcppSafeScriptingProcLogInfo());
    addProc(new WsjcppSafeScriptingProcedureSetValue());
    addProc(new WsjcppSafeScriptingProcedureConcat());
    addProc(new WsjcppSafeScriptingProcMakeDir());
    addProc(new WsjcppSafeScriptingProcNormalizeClassName());
    addProc(new WsjcppSafeScriptingProcCamelCaseToSnakeCase());
    addProc(new WsjcppSafeScriptingProcToUpperCase());
    addProc(new WsjcppSafeScriptingProcWriteFile());
    addProc(new WsjcppSafeScriptingProcCMakeListsTxtAppendWsjcpp());
}

// ---------------------------------------------------------------------

WsjcppSafeScriptingContext::~WsjcppSafeScriptingContext() {
    // TODO cleanup all pointers
    WsjcppLog::warn(TAG, "TODO cleanup all pointers");
}

// ---------------------------------------------------------------------

WsjcppSafeScriptingVariable * WsjcppSafeScriptingContext::addVariable(const std::string &sName) {
    if (hasVariable(sName)) {
        WsjcppLog::err(TAG, "Variable '" + sName + "' already defined");
        return nullptr;
    }
    WsjcppSafeScriptingVariable *pVar = new WsjcppSafeScriptingVariable("");
    m_vVariables[sName] = pVar;
    return pVar;
}

// ---------------------------------------------------------------------

WsjcppSafeScriptingVariable * WsjcppSafeScriptingContext::getVariable(const std::string &sName) {
    std::map<std::string, WsjcppSafeScriptingVariable *>::iterator it;
    it = m_vVariables.find(sName);
    if (it != m_vVariables.end()) {
        return it->second;
    }
    return nullptr;
}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingContext::hasVariable(const std::string &sName) {
    return this->hasVar(sName);
}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingContext::hasVar(const std::string &sName) {
    return m_vVariables.find(sName) != m_vVariables.end();
}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingContext::addProc(WsjcppSafeScriptingProc *pProc) {
    if (this->hasProc(pProc->getName())) {
        WsjcppLog::err(TAG, "Proc already defined '" + pProc->getName() + "'");
        return false;
    }
    m_vProcs[pProc->getName()] = pProc;
    return true;
}

// ---------------------------------------------------------------------

WsjcppSafeScriptingProc *WsjcppSafeScriptingContext::getProc(const std::string &sName) {
    std::map<std::string, WsjcppSafeScriptingProc *>::iterator it;
    it = m_vProcs.find(sName);
    if (it != m_vProcs.end()) {
        return it->second;
    }
    return nullptr;
}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingContext::hasProc(const std::string &sName) {
    return m_vProcs.find(sName) != m_vProcs.end();
}

// ---------------------------------------------------------------------

int WsjcppSafeScriptingContext::exec(
    const std::string &sScriptRootDir,
    const std::string &sScriptFileName, 
    const std::string &sScriptContent, 
    std::vector<std::string> vArgs0
) {
    m_sScriptRootDir = sScriptRootDir;
    m_sScriptFileName = sScriptFileName;
    m_sScriptContent = sScriptContent;

    m_vVariables["rootdir"] = new WsjcppSafeScriptingVariable(m_sScriptRootDir);
    m_vVariables["script_filename"] = new WsjcppSafeScriptingVariable(m_sScriptFileName);
    for (int i = 0; i < vArgs0.size(); i++) {
        std::string sArgName = "arg" + std::to_string(i+1);
        WsjcppLog::info(TAG, sArgName + " = '" + vArgs0[i] + "'");
        m_vVariables[sArgName] = new WsjcppSafeScriptingVariable(vArgs0[i]);
    }
    if (!parseScript()) {
        WsjcppLog::err(TAG, "Parse script failed");
        return -1;
    }
    std::string sError = "";
    for (int i = 0; i < m_vScriptTokens.size(); i++) {
        WsjcppSafeScriptingToken *pToken = m_vScriptTokens[i];
        std::string sToken = pToken->getToken();
        if (sToken == "error") {
            WsjcppLog::err(TAG, "error");
            return -1;
        } else if (sToken == "exit") {
            return 0;
        } else if (sToken == "var") {
            std::string sVarName = m_vScriptTokens[i+1]->getToken();
            i++;
            std::string sEndToken = m_vScriptTokens[i+1]->getToken();
            if (sEndToken != "end") {
                WsjcppLog::err(TAG, "Expected token 'end' after '" + sVarName + "' but got '" + sEndToken + "'");
                return -1;
            }
            i++;
            // TODO check empty name
            if (hasVariable(sVarName)) {
                WsjcppLog::err(TAG, "variable already defined " + sVarName);
                return -1;
            } else if (hasProc(sVarName)) {
                WsjcppLog::err(TAG, "Procedure with this name already exists " + sVarName);
                return -1;
            } else {
                addVariable(sVarName); // TODO add variable
            }
        } else if (hasProc(sToken)) {
            std::vector<WsjcppSafeScriptingVariable *> vArgs2;
            std::vector<WsjcppSafeScriptingVariable *> vRuntimeRemoveAfter;
            std::vector<WsjcppSafeScriptingToken *> vTokenArgs;
            for (int n = i+1; n < m_vScriptTokens.size(); n++) {
                WsjcppSafeScriptingToken *pToken2 = m_vScriptTokens[n];
                std::string sTokenValue2 = pToken2->getToken();
                vTokenArgs.push_back(pToken2);
                if (sTokenValue2 == "end") {
                    i = n;
                    vTokenArgs.pop_back();
                    break;
                } else if (pToken2->hasString()) {
                    WsjcppSafeScriptingVariable *pVar = addVariable("vartmp_" + WsjcppCore::createUuid());
                    pVar->setValue(sTokenValue2);
                    vArgs2.push_back(pVar);
                    vRuntimeRemoveAfter.push_back(pVar);
                } else if (hasVariable(sTokenValue2)) {
                    WsjcppSafeScriptingVariable *pVar = getVariable(sTokenValue2);
                    vArgs2.push_back(pVar);
                } else {
                    WsjcppLog::err(TAG, "Uknown token: " + sTokenValue2);
                    // TODO cleanup 
                    return -1;
                }
            }
            WsjcppSafeScriptingProc *pProcedure = this->getProc(sToken);
            if (!pProcedure->exec(vArgs2)) {
                std::string sDebugInfo = "Procedure: " + sToken + "\n";
                sDebugInfo += "Arguments: \n";
                for (int n = 0; n < vArgs2.size(); n++) {
                    sDebugInfo += "   - " + vArgs2[n]->getValue() + "\n";
                }
                sDebugInfo += "Tokens info:\n";
                sDebugInfo += pToken->getContextForLog() + "\n";
                for (int n = 0; n < vTokenArgs.size(); n++) {
                    sDebugInfo += vTokenArgs[n]->getContextForLog() + "\n";
                }
                WsjcppLog::err(TAG, sDebugInfo);
                return -1;
            };
            for (int n = 0; n < vRuntimeRemoveAfter.size(); n++) {
                delete vRuntimeRemoveAfter[n]; // TODO check
                vRuntimeRemoveAfter[n] = nullptr;
            }
            vRuntimeRemoveAfter.clear();
        } else {
            WsjcppLog::err(TAG, "Unknown token '" + sToken + "'  \n(" + pToken->getContextForLog() + ")");
            return -1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------

bool WsjcppSafeScriptingContext::parseScript() {
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
            m_vScriptTokens.push_back(new WsjcppSafeScriptingToken(sToken, m_sScriptFileName, nLine));
            // WsjcppLog::info(TAG, "Token '" + sToken + "'");
            if (c == '\n') {
                m_vScriptTokens.push_back(new WsjcppSafeScriptingToken("end", m_sScriptFileName, nLine));
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
            m_vScriptTokens.push_back(new WsjcppSafeScriptingToken(sToken, m_sScriptFileName, nLine));
        } else if (n == 10) {
            sToken += c;
        } else if (c == '\n') {
            int nSize = m_vScriptTokens.size();
            if (nSize > 0 && m_vScriptTokens[nSize-1]->getToken() != "end") {
                m_vScriptTokens.push_back(new WsjcppSafeScriptingToken("end", m_sScriptFileName, nLine));
            }
            n = 0;
            nLine++;
        } else if (n == 2) {
            // just skip
        } else {
            std::string sError = "parseScript, Unknown token '";
            sError += c;
            sError += "' in a line: " + m_sScriptFileName + ":" + std::to_string(nLine);
            WsjcppLog::err(TAG, sError);
            return false;
        }
    }
    if (n == 1) {
        m_vScriptTokens.push_back(new WsjcppSafeScriptingToken(sToken, m_sScriptFileName, nLine));
        m_vScriptTokens.push_back(new WsjcppSafeScriptingToken("end", m_sScriptFileName, nLine));
        // WsjcppLog::info(TAG, "parseScript, Last Token '" + sToken + "'");
    }
    return true;
}