//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_SPOUTEXECUTOR_H
#define KATRINA_SPOUTEXECUTOR_H

#include "../base/Executor.h"
#include "ISpout.h"
#include "SpoutOutputCollector.h"

namespace Katrina {
    namespace topology {
        class ITopology;
    }

    namespace message {
        class MessageCommander;
    }

    namespace spout {
        class SpoutExecutor : public base::Executor<spout::ISpout> {
        public:
            SpoutExecutor() : base::Executor<spout::ISpout>(), _needToStop(false) {

            }

            void StopTask() override;

            void OnCreate() override;

            void OnStop() override;

            void SetExecutorIndex(int executorIndex) {
                _executorIndex = executorIndex;
            }

            void SetCommander(message::MessageCommander *commander);

            void RandomDestination(SpoutOutputCollector *outputCollector);

            void GroupDestination(SpoutOutputCollector *outputCollector, int fieldIndex);

        private:
            topology::ITopology *_topology;
            bool _needToStop;
            message::MessageCommander *_commander;
            int _executorIndex;
        };
    }
}

#endif //KATRINA_SPOUTEXECUTOR_H
