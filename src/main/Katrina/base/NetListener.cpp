//
// Created by StevensChew on 17/1/8.
//

#include "../../../../include/main/Katrina/base/NetListener.h"

namespace Katrina {
    namespace net {
        void NetListener::StartListen() {
            meshy::IoLoop::Get()->Start();
            _server.Listen(_host.GetHost(), _host.GetPort());
            _server.OnConnectIndication([=](meshy::IStream *stream) {
                stream->OnDataIndication([stream](const char *buf, int64_t size) mutable {
                    _receiver(stream, buffer, length);
                });
            });
        }
    }
}
