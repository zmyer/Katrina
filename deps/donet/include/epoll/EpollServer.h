//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_EPOLLSERVER_H
#define KATRINA_EPOLLSERVER_H

#include "EpollConnection.h"
#include "../Net.h"

namespace donet {
    class EpollServer : public BasicServer<EpollConnectionPtr> {
    public:
        EpollServer() {

        }

        virtual ~EpollServer() { }

        int32_t Listen(const std::string &host, uint32_t port, int backlog);

        void OnConnectIndication(ConnectIndicationHandler handler) {
            _connectionHandler = handler;
        }

        void OnDisconnecIndication(DisconnectIndicationHandler handler) {
            _disconnectionHandler = handler;
        }

        EpollConnectionPtr Accept(int32_t socketfd);

    private:
        uint32_t _Bind(const std::string &host, uint32_t port);

        DataSink *_dataSink;
        ConnectIndicationHandler _connectionHandler;
        DisconnectIndicationHandler _disconnectionHandler;
    };
}

#endif //KATRINA_EPOLLSERVER_H
