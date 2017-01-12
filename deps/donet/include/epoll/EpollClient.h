//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_EPOLLCLIENT_H
#define KATRINA_EPOLLCLIENT_H

#include <memory>
#include "Net.h"
#include "EpollStream.h"
#include "Net_bsd.h"

namespace donet {
    typedef std::shared_ptr<EpollClient> EpollClientPtr;

    class EpollClient : public EpollStream, public IConnectable {

    public:
        EpollClient(const EpollClient &client) = delete;

        virtual ~EpollClient() { }

        virtual int32_t Receive(char *buffer, int32_t bufferSize, int32_t &readSize) override;

        virtual int32_t Send(const ByteArray &byteArray) override;

        uint32_t GetEvents() const {
            return _events;
        }

        void SetEvents(uint32_t events) {
            _events = events;
        }

        void Connect(const std::string &host, int32_t port) override;

        static EpollClientPtr Connect(const std::string &ip, int32_t port, DataSink *dataSink);

    private:
        EpollClient(NativeSocket clientSocket) : EpollStream(clientSocket) {
            this->SetNativeSocket(clientSocket);
        }

        uint32_t _events;
    };
}

#endif //KATRINA_EPOLLCLIENT_H
