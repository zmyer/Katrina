//
// Created by StevensChew on 17/1/8.
//

#include <thread>
#include "../../../../include/main/Katrina/base/NetConnector.h"

namespace Katrina {
    namespace net {
        void NetConnector::Connect() {
            _client = meshy::TcpClient::Connect(_host.GetHost(), _host.GetPort());
        }

        int32_t NetConnector::SendAndReceive(const char *buffer, int32_t size, char *resultBuffer,
                                             int32_t resultSize) {
            _client->Send(buffer, size);
            bool receiveData = false;
            _client->OnDataIndication([&receiveData](const char *buf, int32_t size) {
                if (resultSize > size) {
                    resultSize = size;
                }

                memcpy(resultBuffer, buf, resultSize);
                receiveData = true;
            });

            while (!receiveData) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            return resultSize;
        }
    }
}