
#include "wsjcpp_yaml.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WSJCppYAMLPlaceInFile

WSJCppYAMLPlaceInFile::WSJCppYAMLPlaceInFile() {
    m_sFilename = "";
    m_nNumberOfLine = 0;
    m_sLine = "";
}

// ---------------------------------------------------------------------

WSJCppYAMLPlaceInFile::WSJCppYAMLPlaceInFile(const std::string &sFilename, int nNumberOfLine, const std::string &sLine) {
    m_sFilename = sFilename;
    m_nNumberOfLine = nNumberOfLine;
    m_sLine = sLine;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLPlaceInFile::getFilename() const {
    return m_sFilename;
}

// ---------------------------------------------------------------------

void WSJCppYAMLPlaceInFile::setFilename(const std::string &sFilename) {
    m_sFilename = sFilename;
}

// ---------------------------------------------------------------------

int WSJCppYAMLPlaceInFile::getNumberOfLine() const {
    return m_nNumberOfLine;
}

// ---------------------------------------------------------------------

void WSJCppYAMLPlaceInFile::setNumberOfLine(int nNumberOfLine) {
    m_nNumberOfLine = nNumberOfLine;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLPlaceInFile::getLine() const {
    return m_sLine;
}

// ---------------------------------------------------------------------

void WSJCppYAMLPlaceInFile::setLine(const std::string &sLine) {
    m_sLine = sLine;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLPlaceInFile::getForLogFormat() {
    return "(" + m_sFilename + ":" + std::to_string(m_nNumberOfLine) + "): " + m_sLine;
}

// ---------------------------------------------------------------------
// WSJCppYAMLItem

WSJCppYAMLItem::WSJCppYAMLItem(
    WSJCppYAMLItem *pParent, 
    const WSJCppYAMLPlaceInFile &placeInFile,
    WSJCppYAMLItemType nItemType
) {
    m_pParent = pParent;
    m_placeInFile.setFilename(placeInFile.getFilename());
    m_placeInFile.setLine(placeInFile.getLine());
    m_placeInFile.setNumberOfLine(placeInFile.getNumberOfLine());
    m_nItemType = nItemType;
    m_bValueHasDoubleQuotes = false;
    m_bNameHasDoubleQuotes = false;
    TAG = "WSJCppYAMLNode";
}

// ---------------------------------------------------------------------

WSJCppYAMLItem::~WSJCppYAMLItem() {
    m_vObjects.clear();
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppYAMLItem::getParent() {
    return m_pParent;
}

// ---------------------------------------------------------------------

WSJCppYAMLPlaceInFile WSJCppYAMLItem::getPlaceInFile() {
    return m_placeInFile;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::setPlaceInFile(const WSJCppYAMLPlaceInFile &placeInFile) {
    m_placeInFile.setFilename(placeInFile.getFilename());
    m_placeInFile.setLine(placeInFile.getLine());
    m_placeInFile.setNumberOfLine(placeInFile.getNumberOfLine());
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::setComment(const std::string &sComment) {
    m_sComment = sComment;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::getComment() {
    return m_sComment;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::setName(const std::string &sName, bool bHasQuotes) {
    m_sName = sName;
    m_bNameHasDoubleQuotes = bHasQuotes;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::hasNameDoubleQuotes() {
    return m_bNameHasDoubleQuotes;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isEmpty() {
    return m_nItemType == WSJCPP_YAML_ITEM_EMPTY;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::doEmpty() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_EMPTY;
    } else {
        WSJCppLog::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isUndefined() {
    return m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::doArray() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_ARRAY;
    } else {
        WSJCppLog::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::doMap() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_MAP;
    } else {
        WSJCppLog::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::doValue() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_VALUE;
    } else {
        WSJCppLog::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isMap() {
    return m_nItemType == WSJCPP_YAML_ITEM_MAP;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::hasElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WSJCppLog::throw_err(TAG, "hasElement('" + sName + "'): Element must be map");
    }
    for (int i = 0; i < m_vObjects.size(); i++) {
        if (m_vObjects[i]->getName() == sName) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppYAMLItem::getElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WSJCppLog::throw_err(TAG, "getElement: Element must be map");
    }
    
    for (int i = 0; i < m_vObjects.size(); i++) {
        if (m_vObjects[i]->getName() == sName) {
            return m_vObjects[i];
        }
    }
    WSJCppLog::throw_err(TAG, "Element '" + sName + "' not found");    
    return nullptr;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::setElement(const std::string &sName, WSJCppYAMLItem *pItem) {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_MAP; // change item type to map on first element  
    }

    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WSJCppLog::throw_err(TAG, "setElement, Element must be 'map' for line(" + std::to_string(pItem->getPlaceInFile().getNumberOfLine()) + "): '" + pItem->getPlaceInFile().getLine() + "'");
    }
    
    if (this->hasElement(sName)) { // TODO remove previous element
        WSJCppLog::throw_err(TAG, "setElement: Map already has element with this name: '" + sName + "'");
    }
    m_vObjects.push_back(pItem); // TODO create clone
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::removeElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WSJCppLog::throw_err(TAG, "removeElement: Element must be map");
    }
    // TODO erase
    return false;
}

// ---------------------------------------------------------------------

std::vector<std::string> WSJCppYAMLItem::getKeys() {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WSJCppLog::throw_err(TAG, "getKeys: Element must be map");
    }
    std::vector<std::string> vKeys;
    for (int i = 0; i < m_vObjects.size(); i++) {
        WSJCppYAMLItem *pItem = m_vObjects[i];
        if (pItem->isValue() || pItem->isMap() || pItem->isArray()) {
            std::string sName = pItem->getName();
            vKeys.push_back(sName);
        }
    }
    return vKeys;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::setElementValue(const std::string &sName, bool bHasNameQuotes, const std::string &sValue, bool bHasValueQuotes) {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_MAP; // change item type to map on first element  
    }

    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WSJCppLog::throw_err(TAG, "setElement, Element must be 'map' for " + this->getPlaceInFile().getForLogFormat());
    }
    
    if (this->hasElement(sName)) {
        WSJCppYAMLItem *pItem = this->getElement(sName);
        pItem->setValue(sValue, bHasValueQuotes);
    } else {
        WSJCppYAMLPlaceInFile pl;
        WSJCppYAMLItem *pNewItem = new WSJCppYAMLItem(this, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
        pNewItem->setName(sName, bHasNameQuotes);
        pNewItem->setValue(sValue, bHasValueQuotes);
        this->setElement(sName, pNewItem);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isArray() {
    return m_nItemType == WSJCPP_YAML_ITEM_ARRAY;
}

// ---------------------------------------------------------------------

int WSJCppYAMLItem::getLength() {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WSJCppLog::throw_err(TAG, "getLength, Element must be array for " + this->getForLogFormat());
    }
    int nCount = 0;
    for (int i = 0; i < m_vObjects.size(); i++) {
        if (!m_vObjects[i]->isEmpty()) {
            nCount++;
        }
    }
    return nCount;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppYAMLItem::getElement(int i) {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WSJCppLog::throw_err(TAG, "getElement, Element must be array");
    }
    int nCounter = -1;
    WSJCppYAMLItem *pItem = nullptr;
    for (int n = 0; n < m_vObjects.size(); n++) {
        if (!m_vObjects[n]->isEmpty()) {
            nCounter++;
            if (nCounter == i) {
                pItem = m_vObjects[n];
                break; 
            }
        }
    }
    if (pItem == nullptr) {
        WSJCppLog::throw_err(TAG, "getElement(" + std::to_string(i) +  "), Out of range in array for '" + this->getPlaceInFile().getLine() + "'");
    }
    return pItem;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::appendElement(WSJCppYAMLItem *pItem) {
    if (pItem->isEmpty()) {
        m_vObjects.push_back(pItem); // TODO clone object
        return true;
    }
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WSJCppLog::throw_err(TAG, "appendElement, Element must be array for " + this->getForLogFormat());
    }
    m_vObjects.push_back(pItem); // TODO clone object
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::removeElement(int i) {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WSJCppLog::throw_err(TAG, "appendElement, Element must be array for " + this->getForLogFormat());
    }
    int nCounter = -1;
    WSJCppYAMLItem *pItem = nullptr;
    for (int n = 0; n < m_vObjects.size(); n++) {
        if (!m_vObjects[n]->isEmpty()) {
            nCounter++;
            if (nCounter == i) {
                pItem = m_vObjects[n];
                break; 
            }
        }
    }
    if (pItem == nullptr) {
        WSJCppLog::throw_err(TAG, "getElement(" + std::to_string(i) +  "), Out of range in array for '" + this->getPlaceInFile().getLine() + "'");
    }
    std::vector<WSJCppYAMLItem *>::iterator it;
    for (it = m_vObjects.begin(); it != m_vObjects.end(); ++it) {
        if (*it == pItem) {
            m_vObjects.erase(it);
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isValue() {
    return m_nItemType == WSJCPP_YAML_ITEM_VALUE;
}

// ---------------------------------------------------------------------

std::string  WSJCppYAMLItem::getValue() {
    if (m_nItemType != WSJCPP_YAML_ITEM_VALUE) {
        WSJCppLog::throw_err(TAG, "getValue, Element must be value for " + this->getForLogFormat());
    }
    return m_sValue;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::setValue(const std::string &sValue, bool bHasQuotes) {
    if (m_nItemType != WSJCPP_YAML_ITEM_VALUE) {
        WSJCppLog::throw_err(TAG, "setValue, Element must be value for " + this->getForLogFormat());
    }
    m_bValueHasDoubleQuotes = bHasQuotes;
    m_sValue = sValue;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::hasValueDoubleQuotes() {
    return m_bValueHasDoubleQuotes;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::toString(std::string sIntent) {
    std::string sRet = "";
    if (this->isValue()) {
        if (m_bValueHasDoubleQuotes) {
            sRet = "\"" + m_sValue + "\"";
        } else {
            sRet = m_sValue;
        }
        if (m_sComment.length() > 0) {
            if (sRet.length() > 0) {
                sRet += " ";
            }
            sRet += "# " + m_sComment;
        }
    } else if (this->isEmpty()) {
        if (m_sComment.length() > 0) {
            sRet += sIntent + "# " + m_sComment;
        }
    } else if (this->isArray()) {
        for (int i = 0; i < m_vObjects.size(); i++) {
            WSJCppYAMLItem *pItem = m_vObjects[i];
            if (pItem->isEmpty()) {
                sRet += sIntent + pItem->toString();
            } else if (pItem->isMap()) {
                std::string s = pItem->toString(sIntent + "  ");
                WSJCppCore::trim(s);
                sRet += sIntent + "- " + s;
            } else {
                sRet += sIntent + "- " + pItem->toString();
            }
            sRet += "\n";
        }
    } else if (this->isMap()) {
        for (int i = 0; i < m_vObjects.size(); i++) {
            WSJCppYAMLItem *pItem = m_vObjects[i];
            if (pItem->isEmpty() ) {
                sRet += sIntent + pItem->toString();
                sRet += "\n";
            } else if (pItem->isArray() || pItem->isMap()) {
                if (pItem->hasNameDoubleQuotes()) {
                    sRet += sIntent + "\"" + pItem->getName() + "\":";
                } else {
                    sRet += sIntent + pItem->getName() + ":";
                }
                if (pItem->getComment().length() > 0) {
                    sRet += " # " + pItem->getComment(); 
                }
                sRet += "\n";
                sRet += pItem->toString(sIntent + "  ");
            } else {
                if (pItem->hasNameDoubleQuotes()) {
                    sRet += sIntent + "\"" + pItem->getName() + "\": " + pItem->toString();
                } else {
                    sRet += sIntent + pItem->getName() + ": " + pItem->toString();
                }
                sRet += "\n";
            }
        }
    } else {
        sRet = "TODO: undefined";
    }
    if (sIntent == "") {
        WSJCppCore::trim(sRet);
    }
    return sRet;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::getItemTypeAsString() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        return "undefined";
    } else if (m_nItemType == WSJCPP_YAML_ITEM_ARRAY) {
        return "array";
    } else if (m_nItemType == WSJCPP_YAML_ITEM_MAP) {
        return "map";
    } else if (m_nItemType == WSJCPP_YAML_ITEM_VALUE) {
        return "value";
    }
    return "unknown";
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::getForLogFormat() {
    return m_placeInFile.getForLogFormat();
}

// ---------------------------------------------------------------------

WSJCppYAMLParsebleLine::WSJCppYAMLParsebleLine(int nLine) {
    TAG = "WSJCppYAMLParsebleLine(line:" + std::to_string(nLine) + ")";
    m_nLine = nLine;
}

// ---------------------------------------------------------------------

WSJCppYAMLParsebleLine::WSJCppYAMLParsebleLine() 
: WSJCppYAMLParsebleLine(-1) {

}

// ---------------------------------------------------------------------

int WSJCppYAMLParsebleLine::getLineNumber() {
    return m_nLine;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::getPrefix() {
    return m_sPrefix;
}

// ---------------------------------------------------------------------

int WSJCppYAMLParsebleLine::getIntent() {
    return m_sPrefix.length();
}

// ---------------------------------------------------------------------

bool WSJCppYAMLParsebleLine::isArrayItem() {
    return m_bArrayItem;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::getComment() {
    return m_sComment;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLParsebleLine::hasNameDoubleQuotes() {
    return m_bNameHasQuotes;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLParsebleLine::isEmptyName() {
    return m_sName.length() == 0;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::getValue() {
    return m_sValue;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLParsebleLine::hasValueDoubleQuotes() {
    return m_bValueHasQuotes;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLParsebleLine::isEmptyValue() {
    return m_sValue.length() == 0;
}

// ---------------------------------------------------------------------

void WSJCppYAMLParsebleLine::parseLine(const std::string &sLine) {
    // reset variables
    m_bArrayItem = false;
    m_sPrefix = "";
    m_sComment = "";
    m_sName = "";
    m_sValue = "";
    m_bNameHasQuotes = false;
    m_bValueHasQuotes = false;

    WSJCppYAMLParserLineStates state = WSJCppYAMLParserLineStates::NO;
    for (int i = 0; i < sLine.length(); i++) {
        char c = sLine[i];
        if ((c == ' ' || c == '\t') && state == WSJCppYAMLParserLineStates::NO) {
            m_sPrefix += c;
        } else if (c == '#' && (state == WSJCppYAMLParserLineStates::NO || state == WSJCppYAMLParserLineStates::VALUE)) {
            state = WSJCppYAMLParserLineStates::COMMENT;
        } else if (state == WSJCppYAMLParserLineStates::COMMENT) {
            if (c != '\r') {
                m_sComment += c;
            }
        } else if (c == '-' && state == WSJCppYAMLParserLineStates::NO) {
            m_bArrayItem = true;
            state = WSJCppYAMLParserLineStates::VALUE;
        } else if ((c != ' ' && c != '\t') && state == WSJCppYAMLParserLineStates::NO) {
            state = WSJCppYAMLParserLineStates::VALUE;
            m_sValue += c;
            if (c == '"') {
                state = WSJCppYAMLParserLineStates::STRING;
            }
        } else if (c == '"' && state == WSJCppYAMLParserLineStates::VALUE) {
            state = WSJCppYAMLParserLineStates::STRING;
            m_sValue += c;
        } else if (c == '\\' && state == WSJCppYAMLParserLineStates::STRING) {
            state = WSJCppYAMLParserLineStates::ESCAPING;
            m_sValue += c;
        } else if (state == WSJCppYAMLParserLineStates::ESCAPING) {
            state = WSJCppYAMLParserLineStates::STRING;
            m_sValue += c;
        } else if (c == '"' && state == WSJCppYAMLParserLineStates::STRING) {
            state = WSJCppYAMLParserLineStates::VALUE;
            m_sValue += c;
        } else if (c == ':' && state == WSJCppYAMLParserLineStates::VALUE) {
            if (m_sName.length() == 0) {
                m_sName = m_sValue;
                m_sValue = ""; // reset value it was param name
            } else {
                m_sValue += c;
            }
        } else if (state == WSJCppYAMLParserLineStates::STRING) {
            m_sValue += c;
        } else if (state == WSJCppYAMLParserLineStates::VALUE) {
            m_sValue += c;
        } else {
            // skip
        }
    }

    if (state == WSJCppYAMLParserLineStates::STRING 
      || state == WSJCppYAMLParserLineStates::ESCAPING
    ) {
        WSJCppLog::throw_err(TAG, "wrong format");
    }

    // split name and value
    /*for (int i = 0; i < m_sNameAndValue.size(); i++) {
        char c = m_sNameAndValue[i];
        if (c == ':' && m_sName.size() == 0) {
            m_sName = m_sValue;
            m_sValue = "";
        } else {
            m_sValue += c;
        }
    }*/
    
    WSJCppCore::trim(m_sName);
    if (m_sName.length() > 0 && m_sName[0] == '"') {
        m_bNameHasQuotes = true;
        m_sName = removeStringDoubleQuotes(m_sName);
    }

    WSJCppCore::trim(m_sValue);
    if (m_sValue.length() > 0 && m_sValue[0] == '"') {
        m_bValueHasQuotes = true;
        m_sValue = removeStringDoubleQuotes(m_sValue);
    }

    WSJCppCore::trim(m_sComment);
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::removeStringDoubleQuotes(const std::string &sValue) {
    if (sValue.size() > 0 && sValue[0] != '"') {
        return sValue;
    }
    int nStartPos = 1;
    int nEndPos = sValue.size()-1;
    std::string sRet = "";
    bool bEscape = false;
    for (int i = nStartPos; i < nEndPos; i++) {
        char c = sValue[i];
        if (bEscape) {
            if (c == 'n') {
                sRet += '\n';
            } else if (c == 'r') {
                sRet += '\r';
            } else {
                sRet += c;
            }
        } else if (c == '\\') {
            bEscape = true;
        } else {
            sRet += c;
        }
    }
    return sRet;
}

// ---------------------------------------------------------------------
// WSJCppYAMLParserStatus

void WSJCppYAMLParserStatus::logUnknownLine(const std::string &sPrefix) {
    WSJCppLog::warn(sPrefix, "Unknown line (" + std::to_string(placeInFile.getNumberOfLine()) + "): '" + placeInFile.getLine() + "' \n"
        + "Current Intent: " + std::to_string(nIntent) +  "\n"
        + "Current Item(line: " + std::to_string(pCurItem->getPlaceInFile().getNumberOfLine()) + "): '" + pCurItem->getPlaceInFile().getLine() + "'"
        + "Current Item(filename: " + pCurItem->getPlaceInFile().getFilename() + "'"
    );
}

// ---------------------------------------------------------------------
// WSJCppYAML

WSJCppYAML::WSJCppYAML() {
    m_pRoot = new WSJCppYAMLItem(nullptr, WSJCppYAMLPlaceInFile(), WSJCPP_YAML_ITEM_MAP);
}

// ---------------------------------------------------------------------

WSJCppYAML::~WSJCppYAML() {
    delete m_pRoot;
}

// ---------------------------------------------------------------------

bool WSJCppYAML::loadFromFile(const std::string &sFileName) {
    std::string sTextContent;
    if (!WSJCppCore::readTextFile(sFileName, sTextContent)) {
        return false;    
    }
    return parse(sFileName, sTextContent);
}

// ---------------------------------------------------------------------

bool WSJCppYAML::saveToFile(const std::string &sFileName) {
    std::string sBuffer = m_pRoot->toString();
    if (!WSJCppCore::writeFile(sFileName, sBuffer)) {
        return false;    
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppYAML::loadFromString(const std::string &sBuffer) {
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppYAML::loadFromString(std::string &sBuffer) {
    return parse("", sBuffer);
}

// ---------------------------------------------------------------------

bool WSJCppYAML::saveToString(std::string &sBuffer) { // TODO move to WSJCppCore
    sBuffer = m_pRoot->toString();
    return true;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppYAML::getRoot() {
    return m_pRoot;
}

// ---------------------------------------------------------------------

std::vector<std::string> WSJCppYAML::splitToLines(const std::string &sBuffer) {
    std::vector<std::string> vLines;
    std::string sLine = "";
    int nSize = sBuffer.length();
    for (int i = 0; i < nSize; i++) {
        char c = sBuffer[i];
        if (c == '\n') {
            vLines.push_back(sLine);
            sLine = "";
        } else {
            sLine += c;
        }
    }
    if (sLine.length() > 0) {
        vLines.push_back(sLine);
    }
    return vLines;
}

// ---------------------------------------------------------------------

bool WSJCppYAML::parse(const std::string &sFileName, const std::string &sBuffer) {
    std::vector<std::string> vLines = this->splitToLines(sBuffer);
    WSJCppYAMLParserStatus st;
    st.pCurItem = m_pRoot; // TODO recreate again new root element
    st.placeInFile.setFilename(sFileName);
    st.nIntent = 0;
    m_pRoot->setPlaceInFile(st.placeInFile);

    for (int nLine = 0; nLine < vLines.size(); nLine++) {
        st.placeInFile.setLine(vLines[nLine]);
        // WSJCppLog::info(TAG, "Line(" + std::to_string(nLine) + ") '" + st.sLine + "'");
        st.placeInFile.setNumberOfLine(nLine);
        st.line = WSJCppYAMLParsebleLine(nLine);
        st.line.parseLine(st.placeInFile.getLine());
        
        bool isEmptyName = st.line.isEmptyName();
        bool isEmptyValue = st.line.isEmptyValue();
        bool isArrayItem = st.line.isArrayItem();
        int nLineIntent = st.line.getIntent();
        int nDiffIntent = nLineIntent - st.nIntent;

        // TODO check comment
        /*if (isEmptyName && isEmptyValue && isArrayItem) {
            continue;
        }*/

        while (nDiffIntent < 0) {
            st.pCurItem = st.pCurItem->getParent();
            st.nIntent = st.nIntent - 2;
            nDiffIntent = nLineIntent - st.nIntent;
            if (st.pCurItem == nullptr) {
                WSJCppLog::throw_err(TAG, "cur item is nullptr");
            }
        }

        if (nDiffIntent == 0) {
            if (st.line.isEmptyName()) {
                if ( ! isEmptyValue && isArrayItem) {
                    process_sameIntent_emptyName_hasValue_arrayItem(st);
                } else if (! isEmptyValue && ! isArrayItem) {
                    process_sameIntent_emptyName_hasValue_noArrayItem(st);
                } else if (isEmptyValue && isArrayItem) {
                    process_sameIntent_emptyName_emptyValue_arrayItem(st);
                } else if (isEmptyValue && ! isArrayItem) {
                    process_sameIntent_emptyName_emptyValue_noArrayItem(st);
                } else {
                    st.logUnknownLine(TAG);
                }
            } else if ( ! st.line.isEmptyName()) {
                if ( ! isEmptyValue && isArrayItem) {
                    process_sameIntent_hasName_hasValue_arrayItem(st);
                } else if ( ! isEmptyValue && ! isArrayItem) {
                    process_sameIntent_hasName_hasValue_noArrayItem(st);
                } else if (isEmptyValue && isArrayItem) {
                    process_sameIntent_hasName_emptyValue_arrayItem(st);
                } else if (isEmptyValue && ! isArrayItem) {
                    process_sameIntent_hasName_emptyValue_noArrayItem(st);
                } else {
                    st.logUnknownLine(TAG);
                }
            } else {
                st.logUnknownLine(TAG);
            }
        } else {
            st.logUnknownLine(TAG);
        }
    }
    return true;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_hasName_emptyValue_arrayItem(WSJCppYAMLParserStatus &st) {
    st.logUnknownLine("process_sameIntent_hasName_emptyValue_arrayItem");
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_hasName_emptyValue_noArrayItem(WSJCppYAMLParserStatus &st) {
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(
        st.pCurItem, st.placeInFile, 
        WSJCppYAMLItemType::WSJCPP_YAML_ITEM_UNDEFINED
    );
    if (st.line.hasValueDoubleQuotes()) {
        pItem->doValue();
        pItem->setValue(st.line.getValue(), st.line.hasValueDoubleQuotes());
    }
    pItem->setName(st.line.getName(), st.line.hasNameDoubleQuotes());
    pItem->setComment(st.line.getComment());
    st.pCurItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_hasName_hasValue_arrayItem(WSJCppYAMLParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WSJCppYAMLItem *pMapItem = new WSJCppYAMLItem(
        st.pCurItem, st.placeInFile, 
        WSJCppYAMLItemType::WSJCPP_YAML_ITEM_MAP
    );
    st.pCurItem->appendElement(pMapItem);
    st.pCurItem = pMapItem;
    st.nIntent = st.nIntent + 2;

    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(
        st.pCurItem, st.placeInFile, 
        WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE
    );
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue(), st.line.hasValueDoubleQuotes());
    pItem->setName(st.line.getName(), st.line.hasNameDoubleQuotes());
    pMapItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_hasName_hasValue_noArrayItem(WSJCppYAMLParserStatus &st) {
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(
        st.pCurItem, st.placeInFile, 
        WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE
    );
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue(), st.line.hasValueDoubleQuotes());
    pItem->setName(st.line.getName(), st.line.hasNameDoubleQuotes());
    st.pCurItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_emptyName_hasValue_arrayItem(WSJCppYAMLParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(
        st.pCurItem, st.placeInFile,
        WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE
    );
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue(), st.line.hasValueDoubleQuotes());
    st.pCurItem->appendElement(pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_emptyName_hasValue_noArrayItem(WSJCppYAMLParserStatus &st) {
    st.logUnknownLine("TODO process_sameIntent_emptyName_hasValue_noArrayItem");
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_emptyName_emptyValue_arrayItem(WSJCppYAMLParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(
        st.pCurItem, st.placeInFile, 
        WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE
    );
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue(), st.line.hasValueDoubleQuotes());
    st.pCurItem->appendElement(pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_emptyName_emptyValue_noArrayItem(WSJCppYAMLParserStatus &st) {
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(
        st.pCurItem, st.placeInFile,
        WSJCppYAMLItemType::WSJCPP_YAML_ITEM_EMPTY
    );
    pItem->setComment(st.line.getComment());
    st.pCurItem->appendElement(pItem);
}

// ---------------------------------------------------------------------

