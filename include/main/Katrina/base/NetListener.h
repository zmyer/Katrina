//
// Created by StevensChew on 17/1/7.
//

#ifndef KATRINA_NETLISTENER_H
#define KATRINA_NETLISTENER_H

#include <functional>
#include "NetAddress.h"

namespace Katrina {
    namespace net {
        typedef std::function<void(std::shared_ptr<meshy::TcpConnection> connection, const char *buffer,
                                   int32_t size)> DataReceiver;

        class NetListener {
        public:
            NetListener(const Katrina::base::NetAddress &host) : _host(host) {

            }

            const Katrina::base::NetAddress &GetHost() const {
                return _host;
            }

            void SetHost(const Katrina::base::NetAddress &host) {
                _host = host;
            }

            virtual void StartListen();

            virtual void DataThreadMain(std::shared_ptr<TcpConnection> connection);

            void OnData(DataReceiver receiver) {
                _receiver = receiver;
            }

        private:
            Katrina::base::NetAddress _host;
            std::shared_ptr<meshy::TcpServer> _server;
            DataReceiver _receiver;
        };
    }
}

#endif //KATRINA_NETLISTENER_H
