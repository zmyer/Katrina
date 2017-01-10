//
// Created by StevensChew on 17/1/8.
//

#include "CommandDispatcher.h"

namespace Katrina {
    namespace message {
        CommandDispatcher &CommandDispatcher::OnCommand(Command::Type::Values type, Handler handler) {
            _handlers[type] = handler;
            return *this;
        }

        void CommandDispatcher::Dispatch(const Command &command) {
            Handler handler = _handlers[command.GetType()];
            handler(command.GetArgs(), command.GetSrc());
        }
    }
}
