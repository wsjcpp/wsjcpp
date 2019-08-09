#ifndef CPPSPM_REPOSITORY_H
#define CPPSPM_REPOSITORY_H

#include <string>
#include <json.hpp>

namespace CppSPM {

class Repository {
    public:
        Repository();
        std::string getUrl();
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonRepository);

    private:
        std::string m_sUrl;
        nlohmann::json m_jsonRepository;
};

} // namespace CppSPM

#endif // CPPSPM_REPOSITORY_H