//
// Created by StevensChew on 17/1/11.
//

#include <memory>
#include "EpollStream.h"
#include "../bsd/Net_bsd.h"

#ifndef KATRINA_EPOLLCONNECTION_H
#define KATRINA_EPOLLCONNECTION_H

namespace donet {
    class EpollConnection : public EpollStream {
    public:
        EpollConnection(NativeSocket nativeSocket) :
                EpollStream(nativeSocket) {

        }

        virtual ~EpollConnection() {

        }

        EpollConnection(const EpollConnection &connection);
    };

    typedef std::shared_ptr<EpollConnection> EpollConnectionPtr;
}
#endif //KATRINA_EPOLLCONNECTION_H
