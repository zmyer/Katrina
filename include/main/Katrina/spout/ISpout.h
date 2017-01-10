//
// Created by xuanyin on 17/1/7.
//

#ifndef KATRINA_ISPOUT_H
#define KATRINA_ISPOUT_H

#include "../base/ITask.h"
#include "../base/OutputCollector.h"

namespace Katrina {
    namespace spout {
        class ISpout : public base::ITask {
        public:
            virtual void Open(base::OutputCollector &outputCollector) = 0;

            virtual void Close() = 0;

            virtual void Execute() = 0;

            virtual ISpout *Clone() const = 0;
        };
    }
}

#endif //KATRINA_ISPOUT_H
