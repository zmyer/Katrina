//
// Created by xuanyin on 17/1/7.
//

#ifndef KATRINA_IBOLT_H
#define KATRINA_IBOLT_H

#include "../base/ITask.h"
#include "../base/OutputCollector.h"
#include "../base/Values.h"

namespace Katrina {
    namespace bolt {
        class IBolt : public base::ITask {
        public:
            virtual void Prepare(base::OutputCollector &outputCollector) = 0;

            virtual void Cleanup() = 0;

            virtual void Execute(const base::Values &values) = 0;

            virtual IBolt *Clone() const = 0;
        };
    }
}

#endif //KATRINA_IBOLT_H
