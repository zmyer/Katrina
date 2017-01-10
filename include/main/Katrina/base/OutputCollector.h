//
// Created by StevensChew on 17/1/7.
//

#ifndef KATRINA_OUTPUTCOLLECTOR_H
#define KATRINA_OUTPUTCOLLECTOR_H


#include <iostream>
#include "Values.h"
#include "../message/SupervisorCommander.h"

using namespace std;

namespace Katrina {
    namespace base {
        class OutputCollector {
        public:
            struct Strategy {
                enum Values {
                    Global = 0,
                    Random = 1,
                    Group = 2
                };
            };

            OutputCollector(const std::string &src, int strategy) : _src(src), _strategy(strategy),
                                                                    _commander(nullptr) { }

            virtual void Emit(const Values &values);

            void SetCommander(Katrina::message::SupervisorCommander *commander) {
                if (_commander) {
                    delete _commander;
                }
                _commander = commander;
            }

            void SetTaskIndex(int taskIndex) {
                _taskIndex = taskIndex;
            }

            void SetGroupField(int groupField) {
                _groupField = groupField;
            }

            int GetGroupField() const {
                return _groupField;
            }

            virtual void RandomDestination() = 0;

            virtual void GroupDestination() = 0;

        private:
            std::string _src;
            int _strategy;
            int _taskIndex;
            Katrina::message::SupervisorCommander *_commander;
            int _groupField;
        };
    }
}

#endif //KATRINA_OUTPUTCOLLECTOR_H
