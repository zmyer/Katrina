//
// Created by StevensChew on 17/1/11.
//

#include "../include/Eventqueueloop.h"

namespace donet {
    EventQueueLoop::EventQueueLoop(EventQueue *queue) : _queue(queue) {

    }

    void EventQueueLoop::_Run() {
        while (true) {
            std::shared_ptr<BaseEvent> event = _queue->PollEvent();
            if (!event)
                continue;
            OnEvent(event);
        }
    }
}