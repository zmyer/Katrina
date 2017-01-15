//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_PACKAGEDATASINK_H
#define KATRINA_PACKAGEDATASINK_H

#include "DataSink.h"
#include "Bytearray.h"
#include "Eventqueue.h"
#include "utils/ThreadPool.h"

namespace donet {
    class PackageDataSink : public DataSink {
    public:
        PackageDataSink(EventQueue *eventQueue);

        ~PackageDataSink();

        int32_t OnDataIndication(IStream *stream, const char *buffer, int32_t size) override;

    private:
        EventQueue *_eventQueue;
        ThreadPool <BaseEvent> *_threadPool;
        ByteArray _data;
        int32_t _totalSize;
    };
}

#endif //KATRINA_PACKAGEDATASINK_H
