#ifndef WSJCPP_AUTHOR_H
#define WSJCPP_AUTHOR_H

#include <string>
#include <json.hpp>

namespace CppSPM {

class Author {
    public:
        Author();
        Author(const std::string &sName);
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonAuthor);
    private:
        std::string m_sName;
        nlohmann::json m_jsonAuthor;
};

} // namespace CppSPM

#endif // WSJCPP_AUTHOR_H