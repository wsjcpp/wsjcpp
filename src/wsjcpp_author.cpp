#include "wsjcpp_author.h"
#include <iostream>

namespace CppSPM {

Author::Author() {
}

Author::Author(const std::string &sName) {
    m_sName = sName;
}

nlohmann::json Author::toJson() {
    m_jsonAuthor["name"] = m_sName;
    return m_jsonAuthor;
}

void Author::fromJson(const nlohmann::json &jsonAuthor) {
    m_jsonAuthor = jsonAuthor;
    for (auto it = jsonAuthor.begin(); it != jsonAuthor.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "name") {
            m_sName = it.value();
        } else {
           std::cout << "IGNORED in authors:  " << sKey << std::endl; 
        }
    }
}


} // namespace CppSPM