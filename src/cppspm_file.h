#ifndef CPPSPM_FILE_H
#define CPPSPM_FILE_H

#include <string>
#include <json.hpp>
#include "cppspm_author.h"
#include "cppspm_server.h"
#include "cppspm_dependence.h"
#include "cppspm_file.h"

namespace CppSPM {

class File {
    public:
        File();
        File(const std::string &sFile);
        std::string getName();
        std::string getSha1();
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonFile);

    private:
        std::string m_sName;
        std::string m_sSha1;
        nlohmann::json m_jsonFile;

};

} // namespace CppSPM

#endif // CPPSPM_FILE_H