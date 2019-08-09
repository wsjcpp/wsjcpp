#ifndef CPPSPM_DEPEDENCE_H
#define CPPSPM_DEPEDENCE_H

#include <string>
#include <json.hpp>

namespace CppSPM {

class Dependence {
    public:
        Dependence();
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonDependence);

    private:
        std::string m_sType;
        std::string m_sFrom;
        std::string m_sName;
        std::string m_sVersion;
        nlohmann::json m_jsonDependece;
};

} // namespace CppSPM

#endif // CPPSPM_DEPEDENCE_H