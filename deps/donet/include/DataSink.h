//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_DATASINK_H
#define KATRINA_DATASINK_H

#include "Net.h"

namespace donet {
    class DataSink {
    public:
        virtual int32_t OnDataIndication(IStream *stream, const char *buffer, int32_t size) = 0;
    };
}
#endif //KATRINA_DATASINK_H
