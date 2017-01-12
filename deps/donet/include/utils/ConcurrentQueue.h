//
// Created by StevensChew on 17/1/11.
//

#ifndef KATRINA_CONCURRENTQUEUE_H
#define KATRINA_CONCURRENTQUEUE_H

#include <queue>
#include <__mutex_base>

namespace donet {
    template<class Type>
    class ConcurrentQueue {
        ConcurrentQueue(const ConcurrentQueue &) = delete;

        ConcurrentQueue &operator=(const ConcurrentQueue &) = delete;

    public:
        ConcurrentQueue() : _queue(), _mutex(), _condition() {

        }

        virtual ~ConcurrentQueue() { }

        void Push(Type record) {
            std::lock_guard<std::mutex> lock_guard(_mutex);
            _queue.push(record);
            _condition.notify_one();
        }

        bool Pop(Type &record, bool isBlock) {
            if (isBlock) {
                std::unique_lock<std::mutex> unique_lock(_mutex);
                while (_queue.empty())
                    _condition.wait(unique_lock);
            }
            else {
                std::lock_guard<std::mutex> lock_guard(_mutex);
                if (_queue.empty())
                    return false;
            }
            record = std::move(_queue.front());
            _queue.pop();
            return true;
        }

        int32_t Size() {
            std::lock_guard<std::mutex> lock_guard(_mutex);
            return _queue.size();
        }

        bool empty() {
            std::lock_guard<std::mutex> lock_guard(_mutex);
            return _queue.empty();
        }

    private:
        std::queue<Type> _queue;
        mutable std::mutex _mutex;
        std::condition_variable _condition;
    };
}
#endif //KATRINA_CONCURRENTQUEUE_H
