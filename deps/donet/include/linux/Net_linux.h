//
// Created by StevensChew on 17/1/14.
//

#ifndef KATRINA_NET_LINUX_H
#define KATRINA_NET_LINUX_H

#include <netinet/in.h>

namespace donet {
    typedef int32_t NativeSocket;
    typedef ::sockaddr_in NativeSocketAddress;
    typedef ::epoll_event NativeSocketEvent;
}
#endif //KATRINA_NET_LINUX_H
