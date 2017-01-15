//
// Created by StevensChew on 17/1/11.
//

#include "../include/Eventqueue.h"
#include "../include/PackageDataSink.h"
#include "../include/utils/ThreadPool.h"
#include "../include/http/HttpRequest.h"
#include "../include/http/HttpResponse.h"

namespace donet {
    PackageDataSink::PackageDataSink(EventQueue *eventQueue) : _eventQueue(eventQueue), _totalSize(0) {
        _threadPool = new ThreadPool<BaseEvent>(10, [&](BaseEvent &event) {
            std::string requestText = event.GetData().ToStdString();
            HttpRequest request;
            request.ParseStdString(requestText);
            HttpResponse response;
            response.SetVersion("HTTP/1.1");
            response.SetStatusCode(200);
            response.SetStatusMessage("OK");
            response.SetContent("Hello");
            event.GetStream()->Send(ByteArray(response.ToStdString()));
        });
    }

    PackageDataSink::~PackageDataSink() {
        if (_threadPool) {
            delete _threadPool;
            _threadPool = nullptr;
        }
    }

    int32_t PackageDataSink::OnDataIndication(IStream *stream, const char *buf, int32_t bytes) {
        _data.Concat(ByteArray(buf, bytes));
        if (_data.size() >= _totalSize) {
            _threadPool->Submit(BaseEvent("data", _data, stream));
            _data.clear();
            _totalSize = 0;
        }
        return bytes;
    }
}