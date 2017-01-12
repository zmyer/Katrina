//
// Created by StevensChew on 17/1/12.
//

#ifndef KATRINA_HTTPDATASINK_H
#define KATRINA_HTTPDATASINK_H

#include "HttpRequest.h"
#include "../Donet.h"

namespace donet {
    class HttpDataSink {
    virtual void OnDataIndication(TcpStream* tcpStream, const HttpRequest& request) = 0;
    };
}
#endif //KATRINA_HTTPDATASINK_H
