//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_EMITTER_H
#define KATRINA_EMITTER_H

#include "../../../../src/type/Values.h"
#include "../base/OutputCollector.h"
#include "IBolt.h"

namespace Katrina {
    namespace bolt {
        class Emitter : public IBolt {
        public:
            virtual void Prepare(base::OutputCollector &outputCollector) {
                _outputCollector = &outputCollector;
            }

            virtual void Cleanup() {

            }

            virtual void Execute(const base::Values &values) {

            }

        private:
            base::OutputCollector *_outputCollector;
        };
    }
}

#endif //KATRINA_EMITTER_H
