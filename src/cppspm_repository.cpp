#include "cppspm_repository.h"
#include <iostream>

namespace CppSPM {

Repository::Repository() {
}

// ---------------------------------------------------------------------

std::string Repository::getUrl() {
    return m_sUrl;
}

// ---------------------------------------------------------------------

nlohmann::json Repository::toJson() {
    m_jsonRepository["url"] = m_sUrl;
    return m_jsonRepository;
}

// ---------------------------------------------------------------------

void Repository::fromJson(const nlohmann::json &jsonRepository) {
    m_jsonRepository = jsonRepository;
    for (auto it = jsonRepository.begin(); it != jsonRepository.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "url") {
            m_sUrl = it.value();
        } else {
           std::cout << "IGNORED in repository:  " << sKey << std::endl; 
        }
    }
}

} // namespace CppSPM