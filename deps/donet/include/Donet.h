//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_DONET_H
#define KATRINA_DONET_H

#ifdef OS_LINUX
#elif defined(OS_WIN32)
#endif

namespace donet {
#ifdef OS_LINUX
#elif defined(OS_WIN32)
#endif
}

#include "epoll/EpollClient.h"
#include "epoll/EpollConnection.h"
#include "epoll/EpollLoop.h"
#include "epoll/EpollServer.h"
#include "epoll/EpollStream.h"

namespace donet {
    typedef EpollServer TcpServer;
    typedef EpollConnection TcpConnection;
    typedef EpollClient TcpClient;
    typedef EpollStream TcpStream;
}

#endif //KATRINA_DONET_H
