//
// Created by StevensChew on 17/1/11.
//

#ifndef KATRINA_HTTPSERVER_H
#define KATRINA_HTTPSERVER_H

#include "../Donet.h"

namespace donet {
    class HttpServer {
    public:
        typedef std::function<void(HttpConnection * connection)> ConnectionHandler;

        HttpServer() {

        }

        virtual ~HttpServer() {

        }

        void Listen(const std::string &host, uint32_t port, int backlog = 10);

        void OnConnectionHandler(ConnectionHandler connectionHandler) {
            _connectionHandler = connectionHandler;
        }

    private:
        TcpServer _server;
        ConnectionHandler _connectionHandler;
    };
}
#endif //KATRINA_HTTPSERVER_H
