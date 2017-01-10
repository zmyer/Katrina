//
// Created by xuanyin on 17/1/7.
//

#ifndef KATRINA_MESSAGELOOP_H
#define KATRINA_MESSAGELOOP_H


class Message;

#include <functional>
#include <map>

namespace Katrina {
    namespace message {
        class MessageLoop {
        public:
            typedef std::function<void(Message *)> MessageHandler;

            MessageLoop();

            MessageLoop(const MessageLoop &) = delete;

            const MessageLoop &operator=(const MessageLoop &) = delete;

            template<class ObjectType, class MethodType>
            void MessageMap(int messageType, ObjectType *self, MethodType method) {
                MessageMap(messageType, std::bind(method, self, std::placeholders::_1));
            };

            void MessageMap(int messageType, MessageHandler handler) {
                _messageHandlers.insert({messageType, handler});
            }

            void Run();

            void Stop();

            void PostMessage(Message *message);

        private:
            std::map<int, MessageHandler> _messageHandlers;
            uint64_t _threadId;
        };
    }
}

#endif //KATRINA_MESSAGELOOP_H
