//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_BASEBATCHBOLT_H
#define KATRINA_BASEBATCHBOLT_H

#include "../base/Fields.h"

namespace Katrina {
    namespace base {
        class BatchOutputCollector;
    }

    namespace bolt {
        class BaseBatchBolt {
        public:
            virtual void Prepare(base::BatchOutputCollector &collector, void *id) = 0;

            virtual void Execute(const base::Values &value) = 0;

            virtual void FinishBatch() = 0;

            virtual base::Fields DeclareOutputFields() = 0;

        private:
            void *_id;
            int _count = 0;
        };
    }
}

#endif //KATRINA_BASEBATCHBOLT_H
