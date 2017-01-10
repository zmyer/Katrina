//
// Created by xuanyin on 17/1/7.
//

#ifndef KATRINA_MESSAGE_H
#define KATRINA_MESSAGE_H
#include <sys/_types/_int32_t.h>

namespace Katrina {
    namespace message {
        class Message {
        public:
            struct Type {
                enum {
                    Stop = 0,
                };
            };

            Message(int32_t type) : _type(type) {

            }

            virtual ~Message() {

            }

            int32_t GetType() const {
                return _type;
            }

            void SetType(int32_t type) {
                _type = type;
            }

        private:
            int32_t _type;
        };
    }
}

#endif //KATRINA_MESSAGE_H
