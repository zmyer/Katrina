//
// Created by StevensChew on 17/1/8.
//

#include "../../../../include/main/Katrina/spout/SpoutOutputCollector.h"

namespace Katrina {
    namespace spout {
        void Katrina::spout::SpoutOutputCollector::RandomDestination() {
            _executor->RandomDestination(this);
        }

        void Katrina::spout::SpoutOutputCollector::GroupDestination() {
            _executor->GroupDestination(this);
        }

        void Katrina::spout::SpoutOutputCollector::Emit(const base::Values &values, int msgId) {

        }
    }
}