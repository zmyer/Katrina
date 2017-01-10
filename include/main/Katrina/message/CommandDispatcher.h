//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_COMMANDDISPATCER_H
#define KATRINA_COMMANDDISPATCER_H

#include <map>
#include "../base/Variant.h"
#include "Command.h"

namespace Katrina {
    namespace message {
        class CommandDispatcher {
        public:
            typedef std::function<void(Katrina::base::Variants args, std::shared_ptr<TcpConnection> src)> Handler;

            CommandDispatcher &OnCommand(Command::Type::Values type, Handler handler);

            void Dispatch(const Command &command);

        private:
            std::map<Command::Type::Values, Handler> _handlers;
        };

    }
}

#endif //KATRINA_COMMANDDISPATCER_H
