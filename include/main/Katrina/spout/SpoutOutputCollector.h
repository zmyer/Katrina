//
// Created by StevensChew on 17/1/8.
//

#include "../base/OutputCollector.h"
#include "../base/Values.h"

#ifndef KATRINA_SPOUTOUTPUTCOLLECTOR_H
#define KATRINA_SPOUTOUTPUTCOLLECTOR_H

namespace Katrina {
    class SpoutExecutor;
    namespace spout {
        class SpoutOutputCollector : public base::OutputCollector {

        public:
            SpoutOutputCollector(const string &src, int strategy, SpoutExecutor *executor) :
                    OutputCollector(src, strategy), _executor(executor) { }

            virtual void RandomDestination() override;

            virtual void GroupDestination() override;

            void Emit(const base::Values &values, int msgId);

        private:
            SpoutExecutor *_executor;
        };
    }
}

#endif //KATRINA_SPOUTOUTPUTCOLLECTOR_H
