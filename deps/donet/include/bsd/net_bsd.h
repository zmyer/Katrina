//
// Created by StevensChew on 17/1/11.
//

#ifndef KATRINA_NET_BSD_H
#define KATRINA_NET_BSD_H

#include <sys/_types/_int32_t.h>

namespace donet {
    typedef int32_t NativeSocket;
    typedef struct sockaddr_in NativeSocketAddress;
}

#endif //KATRINA_NET_BSD_H
