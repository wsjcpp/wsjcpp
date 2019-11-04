#ifndef CPPSPM_FILE_H
#define CPPSPM_FILE_H

#include <string>
#include <json.hpp>
#include "wsjcpp_author.h"
#include "wsjcpp_server.h"
#include "wsjcpp_dependence.h"
#include "wsjcpp_file.h"

namespace CppSPM {

class File {
    public:
        File();
        File(const std::string &sFile);
        std::string getFrom();
        std::string getTo();
        std::string getSha1();
        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonFile);

    private:
        std::string m_sFrom;
        std::string m_sTo;
        std::string m_sSha1;
        nlohmann::json m_jsonFile;

};

} // namespace CppSPM

#endif // CPPSPM_FILE_H