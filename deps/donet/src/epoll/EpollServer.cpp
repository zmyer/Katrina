//
// Created by StevensChew on 17/1/14.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../../include/epoll/EpollServer.h"
#include "../../include/epoll/EpollLoop.h"
#include "../../include/linux/Net_linux.h"

using namespace std;

namespace donet {
    int32_t EpollServer::_Bind(const std::string &host, uint32_t port) {
        int32_t listenfd;
        if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            exit(1);
        }

        SetNativeSocket(listenfd);
        int32_t option = 1;
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
        donet::SetNonBlocking(listenfd);

        NativeSocketAddress address;
        bzero(&address, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = inet_addr(host.c_str());
        int32_t errorCode = bind(listenfd, (struct sockaddr *) &address, sizeof(address));

        if (errorCode < 0) {
            return errorCode;
        }
        return 0;
    }

    int32_t EpollServer::Listen(const std::string &host, int32_t port, int backlog) {
        _Bind(host, port);
        int32_t listenfd = GetNativeSocket();
        int32_t errorCode = listen(listenfd, backlog);

        if (errorCode == -1) {
            return errorCode;
        }
        errorCode = EpollLoop::Get()->AddEpollEvent(EPOLLIN, listenfd);
        if (errorCode == -1) {
            return errorCode;
        }
        this->SetDataSink(dataSink);
        EpollLoop::Get()->AddServer(listenfd, this);
    }

    void SetNonBlocking(int32_t sock);

    EpollConnectionPtr EpollServer::Accept(int32_t socketfd) {
        int32_t conn_sock;;
        int32_t addrLen;
        int32_t remote;

        int32_t listenfd = GetNativeSocket();
        while ((conn_sock = accept(listenfd, (struct sockaddr *) &remote,
                                   (socklen_t *) &addrLen)) > 0) {
            donet::SetNonBlocking(conn_sock);
            NativeSocketEvent ev;
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = conn_sock;
            if (epoll_ctl(sockfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
                exit(EXIT_FAILURE);
            }
            EpollConnectionPtr connection = std::make_shared<EpollConnection>(conn_sock);
            if (_connectionHandler) {
                _connectionHandler(connection.get());
            }
            connection->SetDataSink(this->GetDataSink());
            return connection;
        }

        if (conn_sock == -1) {
            if (errno != EAGAIN && errno != ECONNABORTED
                && errno != EPROTO && errno != EINTR) {
                perror("accept");
            }
        }
        return EpollConnectionPtr(nullptr);
    }
}
