//
// Created by StevensChew on 17/1/7.
//

#ifndef KATRINA_ITASK_H
#define KATRINA_ITASK_H


#include <vector>
#include "Fields.h"

namespace Katrina {
    namespace base {
        class ITask {
        public:
            virtual ~ITask() { };

            virtual Fields DeclareFields() const = 0;
        };
    }
}

#endif //KATRINA_ITASK_H
