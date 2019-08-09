#include "cppspm_file.h"
#include <iostream>

namespace CppSPM {

File::File() {
}

// ---------------------------------------------------------------------

File::File(const std::string &sFile) {
    m_sName = sFile;
}

// ---------------------------------------------------------------------

std::string File::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string File::getSha1() {
    return m_sSha1;
}

// ---------------------------------------------------------------------

nlohmann::json File::toJson() {
    m_jsonFile["name"] = m_sName;
    m_jsonFile["sha1"] = m_sSha1;
    return m_jsonFile;
}

// ---------------------------------------------------------------------

void File::fromJson(const nlohmann::json &jsonFile) {
    m_jsonFile = jsonFile;
    for (auto it = jsonFile.begin(); it != jsonFile.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "name") {
            m_sName = it.value();
        } else if (sKey == "sha1") {
            m_sSha1 = it.value();
        } else {
           std::cout << "IGNORED in file:  " << sKey << std::endl; 
        }
    }
}

} // namespace CppSPM