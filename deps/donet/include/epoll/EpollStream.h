//
// Created by StevensChew on 17/1/11.
//

#include "../Net.h"

#ifndef KATRINA_EPOLLSTREAM_H
#define KATRINA_EPOLLSTREAM_H

namespace donet {
    class EpollStream : public BasicStream {
    public:
        EpollStream(NativeSocket nativeSocket) : BasicStream(nativeSocket) {

        }

        virtual ~EpollStream() {

        }

        EpollStream(const EpollStream &stream) = delete;

        virtual int32_t Receive(char *buffer, int32_t bufferSize, int32_t &readSize) override;

        virtual int32_t Send(const ByteArray &byteArray) override;

        uint32_t GetEvents() const {
            return _events;
        }

        void SendEvents(uint32_t events) {
            _events = events;
        }

        void OnDataIndication(DataIndicateHandler handler) {
            _dataHandler = handler;
        }

        DataIndicateHandler GetDataIndication() const {
            return _dataHandler;
        }

    private:
        uint32_t _events;
        DataIndicateHandler _dataHandler;
    };

    typedef std::shared_ptr<EpollStream> EpollStreamPtr;
}
#endif //KATRINA_EPOLLSTREAM_H
