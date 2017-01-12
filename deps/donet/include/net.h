//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_NET_H
#define KATRINA_NET_H

#ifdef OS_WIN32
#elif defined(OS_BSD)
#elif defined(OS_LINUX)
#endif

#if defined(OS_BSD) || defined(OS_LINUX)
#include <unisted.h>
#include <netinet/in.h>
#endif


#include <functional>
#include "DataSink.h"
#include "Bytearray.h"
#include "bsd/Net_bsd.h"

namespace donet {
    class Socket {
    public:
        Socket() : _nativeSocket(0) {

        }

        Socket(NativeSocket nativeSocket) : _nativeSocket(nativeSocket) {

        }

        virtual ~Socket() {
            Close(_nativeSocket);
        }

        NativeSocket GetNativeSocket() const {
            return _nativeSocket;
        }

        void SetNativeSocket(NativeSocket nativeSocket) {
            _nativeSocket = nativeSocket;
        }

    private:
        NativeSocket _nativeSocket;
    };

    class IStream {
    public:
        typedef std::function<void(const char *buffer, int32_t size)> DataIndicateHandler;

        virtual int32_t Receive(char *buffer, int32_t bufferSize, int32_t &readSize) = 0;

        virtual int32_t Send(const ByteArray &byteArray) = 0;

        virtual void OnDataIndication(DataIndicateHandler handler) = 0;

        virtual DataIndicateHandler GetDataIndication() = 0;
    };

    class IConnectable {
    public:
        virtual void Connect(const std::string &host, int32_t port) = 0;
    };

    template<class ConnectionType>
    class BasicServer : public Socket {
    public:
        typedef std::function<void(IStream *stream)> ConnectIndicationHandler;
        typedef std::function<void(IStream *stream)> DisconnectIndicationHandler;

        BasicServer() {

        }

        virtual int32_t Listen(const std::string &host, int32_t port, int backlog) = 0;

        virtual void OnConnectIndication(ConnectIndicationHandler handler) = 0;

        virtual void ONDisconnectIndication(DisconnectIndicationHandler handler) = 0;

        virtual ConnectionType Accept(int32_t listenfd) = 0;
    };

    class BasicStream : public IStream, public Socket {
    public :
        BasicStream() = default;

        BasicStream(NativeSocket nativeSocket) : Socket(nativeSocket) {
        }

        BasicStream(const BasicStream &stream) = delete;

        virtual void SetDataSink(DataSink *dataSink) {
            _dataSink = dataSink;
        }

        virtual DataSink *GetDataSink() const {
            return _dataSink;
        }

    private:
        DataSink *_dataSink;
    };

}
#endif //KATRINA_NET_H
