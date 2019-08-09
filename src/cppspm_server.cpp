#include "cppspm_server.h"
#include <iostream>

namespace CppSPM {

Server::Server() {

}

// ---------------------------------------------------------------------

Server::Server(const std::string &sAddress) {
    m_sAddress = sAddress;
}

// ---------------------------------------------------------------------

std::string Server::getAddress() {
    return m_sAddress;
}

// ---------------------------------------------------------------------

nlohmann::json Server::toJson() {
    m_jsonServer["address"] = m_sAddress;
    return m_jsonServer;
}

// ---------------------------------------------------------------------

void Server::fromJson(const nlohmann::json &jsonServer) {
    m_jsonServer = jsonServer;
    for (auto it = jsonServer.begin(); it != jsonServer.end(); ++it) {
        std::string sKey = it.key();
        if (sKey == "address") {
            m_sAddress = it.value();
        } else {
           std::cout << "IGNORED in server:  " << sKey << std::endl; 
        }
    }
}

} // namespace CppSPM