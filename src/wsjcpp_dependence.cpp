#include "wsjcpp_dependence.h"
#include <iostream>

namespace CppSPM {

Dependence::Dependence() {
}

// ---------------------------------------------------------------------

std::string Dependence::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

std::string Dependence::getFrom() {
    return m_sFrom;
}

// ---------------------------------------------------------------------

std::string Dependence::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string Dependence::getVersion() {
    return m_sVersion;
}

// ---------------------------------------------------------------------

nlohmann::json Dependence::toJson() {
    m_jsonDependece["type"] = m_sType;
    m_jsonDependece["from"] = m_sFrom;
    m_jsonDependece["name"] = m_sName;
    m_jsonDependece["version"] = m_sVersion;
    return m_jsonDependece;
}

// ---------------------------------------------------------------------

void Dependence::fromJson(const nlohmann::json &jsonDependece) {
    m_jsonDependece = jsonDependece;
    for (auto it = jsonDependece.begin(); it != jsonDependece.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "type") {
            m_sType = it.value();
        } else if (sKey == "from") {
            m_sFrom = it.value();
        } else if (sKey == "name") {
            m_sName = it.value();
        } else if (sKey == "version") {
            m_sVersion = it.value();
        } else {
           std::cout << "IGNORED in dependence:  " << sKey << std::endl; 
        }
    }
}

} // namespace CppSPM