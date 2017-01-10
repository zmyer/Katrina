//
// Created by xuanyin on 17/1/7.
//

#ifndef KATRINA_MESSAGELOOPMANAGER_H
#define KATRINA_MESSAGELOOPMANAGER_H

#include <iosfwd>
#include <memory>
#include "Message.h"
#include "MessageLoop.h"

namespace Katrina {
    namespace message {
        class MessageLoopManager {
        public:
            static MessageLoopManager &GetInstance() {
                static MessageLoopManager manager;
                return manager;
            }

            MessageLoopManager(const MessageLoopManager &) = delete;

            const MessageLoopManager &operator=(const MessageLoopManager &) = delete;

            void Register(const std::string &name, MessageLoop *loop) {
                _messageLoops.insert({name, std::shared_ptr<MessageLoop>(loop)});
            }

            void PostMessage(const std::string &name, Message *message) {
                auto messageLoopPair = _messageLoops.find(name);
                if (messageLoopPair != _messageLoops.end()) {
                    messageLoopPair->second->PostMessage(message);
                }
            }

        private:
            MessageLoopManager() { }

            std::map<std::string, std::shared_ptr<MessageLoop>> _messageLoops;
        };
    }
}

#endif //KATRINA_MESSAGELOOPMANAGER_H
