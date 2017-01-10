//
// Created by xuanyin on 17/1/7.
//

#ifndef KATRINA_BOLTEXECUTOR_H
#define KATRINA_BOLTEXECUTOR_H

#include "IBolt.h"
#include "../topology/ITopology.h"
#include "../base/Executor.h"
#include "BoltOutputCollector.h"

namespace Katrina {
    namespace bolt {
        class BoltExecutor : public base::Executor<Katrina::bolt::IBolt> {
        public:
            BoltExecutor() : Katrina::base::Executor<Katrina::bolt::IBolt>() {

            }

            void StopTask() override;

            void OnCreate() override;

            void OnStop() override;

            void SetExecutorIndex(int executorIndex) {
                _executorIndex = executorIndex;
            }

            void SendData(const base::Values &values);

            void OnData(const base::Values &values);

            void SetCommander(message::SupervisorCommander *commander) {
                _commander = commander;
            }

            void RandomDestination(BoltOutputCollector *outputCollector);

            void GroupDestination(BoltOutputCollector *outputCollector, int fieldIndex);

        private:
            Katrina::topology::ITopology *_topology;
            message::SupervisorCommander *_commander;
            int _executorIndex;
        };
    }
}


#endif //KATRINA_BOLTEXECUTOR_H
