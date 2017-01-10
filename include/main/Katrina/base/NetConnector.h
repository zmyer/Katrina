//
// Created by StevensChew on 17/1/7.
//

#ifndef KATRINA_NETCONNECTOR_H
#define KATRINA_NETCONNECTOR_H

#include <memory>
#include "NetAddress.h"

namespace Katrina {
    namespace net {
        class NetConnector {
        public:
            NetConnector(Katrina::base::NetAddress &host) : _host(host) {

            }

            const Katrina::base::NetAddress &GetHost() const {
                return _host;
            }

            void SetHost(const Katrina::base::NetAddress &host) {
                _host = host;
            }

            virtual void Connect();

            int32_t SendAndReceive(const char *buffer, int32_t size, char *resultBuffer, int32_t resultSize);

        private:
            Katrina::base::NetAddress _host;
            std::shared_ptr<meshy::TcpClient> _client;
        };
    }
}

#endif //KATRINA_NETCONNECTOR_H
