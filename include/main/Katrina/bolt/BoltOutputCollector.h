//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_BOLTOUTPUTCOLLECTOR_H
#define KATRINA_BOLTOUTPUTCOLLECTOR_H

#include "../base/OutputCollector.h"
#include "../base/Values.h"

namespace Katrina {
    namespace bolt {
        class BoltExecutor;

        class BoltOutputCollector : public base::OutputCollector {
        public:
            BoltOutputCollector(const std::string &src, int strategy, BoltExecutor *executor) :
                    base::OutputCollector(src, strategy), _executor(executor) {

            }

            virtual void RandomDestination() override;

            virtual void GroupDestination() override;

            void Ack(const base::Values &values);

            void Fail(const base::Values &values);

        private:
            BoltExecutor *_executor;
        };
    }
}

#endif //KATRINA_BOLTOUTPUTCOLLECTOR_H
