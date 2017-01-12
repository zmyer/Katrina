//
// Created by StevensChew on 17/1/11.
//

#include "../include/Eventqueue.h"
#include "../include/PackageDataSink.h"
#include "../include/utils/ThreadPool.h"

namespace donet {
    PackageDataSink::PackageDataSink(EventQueue *eventQueue) :_eventQueue(eventQueue), _totalSize(0) {
        _threadPool = new ThreadPool<BaseEvent>(10, [&](BaseEvent& event) {
            std::string requestText = event.GetData().ToStdString();
        })
    }
}