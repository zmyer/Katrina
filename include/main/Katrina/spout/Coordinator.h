//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_COORDINATOR_H
#define KATRINA_COORDINATOR_H

#include "../base/OutputCollector.h"
#include "ISpout.h"

namespace Katrina {
    namespace spout {
        class Coordinator : public ISpout {
        public:
            virtual void Open(base::OutputCollector &outputCollector) {
                _outputCollector = &outputCollector;
            }

            virtual void Close() {

            }

            virtual void Execute() {

            }

        private:
            base::OutputCollector *_outputCollector;
        };
    }
}
#endif //KATRINA_COORDINATOR_H
