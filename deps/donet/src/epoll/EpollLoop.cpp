//
// Created by StevensChew on 17/1/14.
//

#include <signal.h>
#include <thread>
#include "../../include/epoll/EpollLoop.h"
#include "../../include/linux/Net_linux.h"
#include "../../include/IoLoop.h"

namespace donet {
    EpollLoop *EpollLoop::Get() {
        static EpollLoop epollLoop;
        return &epollLoop;
    }

    EpollLoop::EpollLoop() {
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGPIPE);
        sigprocmask(SIG_BLOCK, &set, NULL);
        _Initialize();
    }

    EpollLoop::~EpollLoop() { _shutdown = true }

    void EpollLoop::AddServer(NativeSocket socket, EpollServer *server) {
        _servers.insert({socket, server});
    }

    void EpollLoop::AddStream(EpollStreamPtr epollStreamPtr) {
        _streams[epollStreamPtr->GetNativeSocket()] = epollStreamPtr;
    }

    int32_t EpollLoop::AddEpollEvent(int32_t events, int32_t fd) {
        NativeSocketEvent ev;
        ev.events = events;
        ev.data.fd = fd;
        return epoll_ctl(_eventfd, EPOLL_CTL_ADD, fd, &ev);
    }

    int32_t EpollLoop::ModifyEpollEvents(int32_t events, int32_t fd) {
        NativeSocketEvent ev;
        ev.events = events;
        ev.data.fd = fd;
        return epoll_ctl(_eventfd, EPOLL_CTL_MOD, fd, &ev);

    }

    void EpollLoop::_Initialize() {
        _eventfd = epoll_create(MAX_EVENT_COUNT);
        if (_eventfd == -1) {
        }
    }

    void EpollLoop::_Run() {
        auto func = std::bind(&EpollLoop::_EpollThread, this);
        std::thread listenThread(func);
        listenThread.detach();
    }

    void EpollLoop::_EpollThread() {
        NativeSocketEvent events[MAX_EVENT_COUNT];
        while (!_shutdown) {
            int32_t nfds;
            nfds = epoll_wait(_eventfd, events, MAX_EVENT_COUNT, -1);
            if (-1 == nfds) {
                exit(EXIT_FAILURE);
            }
            _HandlerEvent(_eventfd, events, nfds);
        }
    }

    void EpollLoop::_HandlerEvent(int32_t eventfd, struct epoll_event *events, int32_t nfds) {
        for (int i = 0; i < nfds; i++) {
            int32_t fd;
            fd = events[i].data.fd;
            if (_servers.find(fd) != _servers.end()) {
                _Accept(eventfd, fd);
                continue;
            }
            int32_t n = 0;
            if (events[i].events & EPOLLIN) {
                _Read(eventfd, fd, events[i].events);
            }
            if (events[i].events & EPOLLOUT) {

            }
        }
    }

}
