//
// Created by StevensChew on 17/1/11.
//

#ifndef KATRINA_EVENTQUEUELOOP_H
#define KATRINA_EVENTQUEUELOOP_H

#include "Eventqueue.h"

namespace donet {
    class EventQueueLoop : public Loop {
    public:
        EventQueueLoop(EventQueue *queue) :
                _queue(queue) {
        }

    protected:
        virtual void _Run();

        virtual void OnEvent(std::shared_ptr<BaseEvent> event) = 0;

    private:
        EventQueue *_queue;
    };
}

#endif //KATRINA_EVENTQUEUELOOP_H
