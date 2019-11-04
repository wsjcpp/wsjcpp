#include "wsjcpp_file.h"
#include <iostream>

namespace CppSPM {

File::File() {
}

// ---------------------------------------------------------------------

File::File(const std::string &sFile) {
    m_sFrom = sFile;
}

// ---------------------------------------------------------------------

std::string File::getFrom() {
    return m_sFrom;
}

// ---------------------------------------------------------------------

std::string File::getTo() {
    return m_sFrom;
}

// ---------------------------------------------------------------------

std::string File::getSha1() {
    return m_sSha1;
}

// ---------------------------------------------------------------------

nlohmann::json File::toJson() {
    m_jsonFile["from"] = m_sFrom;
    m_jsonFile["to"] = m_sTo;
    m_jsonFile["sha1"] = m_sSha1;
    return m_jsonFile;
}

// ---------------------------------------------------------------------

void File::fromJson(const nlohmann::json &jsonFile) {
    m_jsonFile = jsonFile;
    for (auto it = jsonFile.begin(); it != jsonFile.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "from") {
            m_sFrom = it.value();
        } else if (sKey == "to") {
            m_sTo = it.value();
        } else if (sKey == "sha1") {
            m_sSha1 = it.value();
        } else {
           std::cout << "IGNORED in file:  " << sKey << std::endl; 
        }
    }
}

} // namespace CppSPM