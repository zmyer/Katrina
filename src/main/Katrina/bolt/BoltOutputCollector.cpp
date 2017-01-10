//
// Created by StevensChew on 17/1/8.
//

#include "../../../../include/main/Katrina/bolt/BoltOutputCollector.h"

namespace Katrina {
    namespace bolt {
        void Katrina::bolt::BoltOutputCollector::RandomDestination() {
            _executor->RandomDestination(this);
        }

        void Katrina::bolt::BoltOutputCollector::GroupDestination() {
            _executor->GroupDestination(this, GetGroupField());
        }

        void Katrina::bolt::BoltOutputCollector::Ack(const base::Values &values) {
        }

        void Katrina::bolt::BoltOutputCollector::Fail(const base::Values &values) {

        }
    }
}