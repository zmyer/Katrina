//
// Created by StevensChew on 17/1/7.
//

#ifndef KATRINA_NETADDRESS_H
#define KATRINA_NETADDRESS_H

#include <iostream>

using namespace std;

namespace Katrina {
    namespace base {
        class NetAddress {
        public:
            NetAddress(const std::string &host, int port) : _host(host), _port(port) {

            }

            void SetHost(const std::string host) {
                _host = host;
            }

            const std::string GetHost() const {
                return _host;
            }

            void SetPort(int port) {
                _port = port;
            }

            int GetPort() const {
                return _port;
            }

        private:
            std::string _host;
            int _port;
        };
    }
}

#endif //KATRINA_NETADDRESS_H
