//
// Created by StevensChew on 17/1/11.
//

#ifndef KATRINA_THREADPOOL_H
#define KATRINA_THREADPOOL_H

#include <functional>
#include <thread>
#include <vector>
#include "ConcurrentQueue.h"

namespace donet {
    template<class Type>
    class ThreadPool {
        ThreadPool &operator=(const ThreadPool &threadPool) = delete;

        ThreadPool(const ThreadPool threadPool) = delete;

    public:
        ThreadPool(int32_t threads, std::function<void(Type &record)> handler);

        virtual ~ThreadPool() { }

        void Submit(Type record);

    private:
        bool _shutdown;
        int32_t _threads;
        std::function<void(Type &record)> _handler;
        std::vector<std::thread> _workers;
        ConcurrentQueue<Type> _tasks;
    };
}
#endif //KATRINA_THREADPOOL_H
