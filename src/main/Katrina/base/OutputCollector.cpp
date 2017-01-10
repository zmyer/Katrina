//
// Created by StevensChew on 17/1/8.
//

#include "../../../../include/main/Katrina/base/OutputCollector.h"
#include "../../../../include/main/Katrina/base/Values.h"

namespace Katrina {
    namespace base {
        void OutputCollector::Emit(const Values &values) {
            if (_strategy == Strategy::Global) {
                if (_commander) {
                    _commander->SendTuple(values);
                }
            } else if (_strategy == Strategy::Random) {
                this->RandomDestination();
                _commander->SendTuple(values);
            } else if (_strategy == Strategy::Group) {
                this->GroupDestination();
                _commander->SendTuple(values);
            }
        }
    }
}