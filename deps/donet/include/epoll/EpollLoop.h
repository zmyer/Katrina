//
// Created by StevensChew on 17/1/11.
//

#ifndef KATRINA_EPOLLLOOP_H
#define KATRINA_EPOLLLOOP_H

#include <sys/_types/_int32_t.h>
#include <map>
#include "../loop.h"
#include "EpollStream.h"
#include "EpollServer.h"

namespace donet {
    class EpollLoop : public Loop {
    public:
        static EpollLoop *Get();

        virtual ~EpollLoop() { }

        void AddServer(NativeSocket socket, EpollServer *server);

        void AddStream(EpollStreamPtr epollStreamPtr);

        int32_t AddEpollEvent(int32_t events, int32_t fd);

        int32_t ModifyEpollEvents(int32_t events, int32_t fd);

    protected:
        EpollLoop();

        virtual void _Run() override;

    private:
        void _Initialize();

        void _EpollThread();

        void _HandlerEvent(int32_t eventfd, struct epoll_event *events, int32_t nfds);

        int32_t _Accept(int32_t eventfd, int32_t listenfd);

        void _Read(int32_t eventfd, int32_t fd, int32_t events);

        void _Enqueue(EpollStreamPtr connection, const char *buffer, int32_t nread);

    private:
        int32_t _evnetfd;
        bool _shutdown;
        std::map<NativeSocket, EpollServer *> _servers;
        std::map<NativeSocket, EpollStreamPtr> _streams;
    };
}

#endif //KATRINA_EPOLLLOOP_H
