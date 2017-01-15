//
// Created by StevensChew on 17/1/14.
//

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../../include/epoll/EpollClient.h"
#include "../../include/epoll/EpollLoop.h"

using namespace std;

namespace donet {
    void EpollClient::Connect(const std::string &host, int32_t port) {
        struct sockaddr_in server_addr;
        bzero((char *) &server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(host.c_str());
        server_addr.sin_port = port;
        donet::SetNonBlocking(GetNativeSocket());
        connect(GetNativeSocket(), (struct sockaddr *) &server_addr, sizeof(server_addr));
    }

    EpollClientPtr EpollClient::Connect(const std::string &host, int32_t port, DataSink *dataSink) {
        int32_t clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        EpollClientPtr client = EpollClientPtr(new EpollClient(clientSocket));
        client->SetDataSink(dataSink);
        client->Connect(host, host);

        EpollLoop *epollLoop = EpollLoop::Get();
        client->_events = EPOLLIN | EPOLLET;
        if (epollLoop->AddEpollEvent(client->_events, clientSocket) == -1) {
            perror("epoll_ctl:add");
            exit(EXIT_FAILURE);
        }
        epollLoop->AddStream(client);
        return client;
    }

    int32_t EpollClient::Receive(char *buffer, int32_t bufferSize, int32_t &readSize) {
        readSize = 0;
        int32_t nread = 0;
        NativeSocketEvent en;
        while ((nread = read(GetNativeSocket(), buffer + readSize, bufferSize - 1)) > 0) {
            readSize += nread;
        }
        return nread;
    }

    int32_t EpollClient::Send(const ByteArray &byteArray) {
        struct epoll_event ev;
        NativeSocket clientSocket = GetNativeSocket();
        if (EpollLoop::Get()->ModifyEpollEvents(_events | EPOLLOUT, clientSocket)) {
        }
        const char *buffer = byteArray.data();
        int32_t size = byteArray.size();
        int32_t n = size;

        while (n > 0) {
            int32_t nwrite = write(clientSocket, buffer + size - n, n);
            if (nwrite < n) {
                if (nwrite == -1 && errno != EAGAIN) {
                }
                break;
            }
            n -= nwrite;
        }
        return 0;
    }


}
