//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_EVENTQUEUE_H
#define KATRINA_EVENTQUEUE_H

#include "bytearray.h"
#include "net.h"

namespace donet {
    class BaseEvent {
    public:
        BaseEvent() {

        }

        BaseEvent(std::string type, const ByteArray &data, IStream *stream) :
                _type(type), _data(data), _stream(stream) {

        }

        void SetData(const ByteArray &data) {
            _data = data;
        }

        const ByteArray &GetData() const {
            return _data;
        }

        void SetType(const std::string type) {
            _type = type;
        }

        const std::string GetType() const {
            return _type;
        }

        void SetStream(IStream *stream) {
            _stream = stream;
        }

        IStream *GetStream() const {
            return _stream;
        }

    private:
        std::string &_type;
        ByteArray _data;
        IStream *_stream;
    };

    class EventQueue {
    public:
        EventQueue(int timeout = 0) : _timeout(timeout) {

        }

        void PostEvent(BaseEvent *baseEvent) {
            std::unique_lock<std::mutex> lock(_mutex);
            _events.push_back(std::shared_ptr<BaseEvent>(baseEvent));
        }

        std::shared_ptr<BaseEvent> PollEvent() {
            std::unique_lock<std::mutex> lock(_mutex);
            if (_events.empty()) {
                if (_timeout == 0)
                    return nullptr;
                _waitCondition.wait_for(lock, std::chrono::milliseconds(_timeout));
            }
            if (!_events.empty()) {
                std::shared_ptr<BaseEvent> event = _events.front();
                _events.erase(_events.begin());
                return event;
            }
            return nullptr;
        }

    private:
        std::vector<std::shared_ptr<BaseEvent>> _events;
        std::mutex _mutex;
        std::condition_variable _waitCondition;
        int _timeout;
    };
}

#endif //KATRINA_EVENTQUEUE_H
