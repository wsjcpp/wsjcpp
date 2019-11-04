#ifndef CPPSPM_SERVER_H
#define CPPSPM_SERVER_H

#include <string>
#include <json.hpp>

namespace CppSPM {

class Server {
    public:
        Server();
        Server(const std::string &sAddress);
        std::string getAddress();

        nlohmann::json toJson();
        void fromJson(const nlohmann::json &jsonServer);
        
    private:
        std::string m_sAddress;
        nlohmann::json m_jsonServer;
};

} // namespace CppSPM

#endif // CPPSPM_SERVER_H