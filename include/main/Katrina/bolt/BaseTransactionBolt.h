//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_BASETRANSACTIONBOLT_H
#define KATRINA_BASETRANSACTIONBOLT_H

#include "BaseBatchBolt.h"
#include "TransactionAttempt.h"

namespace Katrina {
    namespace base {
        class BatchOutputCollector;
    }
    namespace bolt {
        class BaseTransactionBolt : public BaseBatchBolt {
        public:
            virtual void Prepare(base::BatchOutputCollector &collector,
                                 TransactionAttempt *attempt) = 0;

            void Prepare(base::BatchOutputCollector &collector, void *id) {

            }
        };
    }
}

#endif //KATRINA_BASETRANSACTIONBOLT_H
