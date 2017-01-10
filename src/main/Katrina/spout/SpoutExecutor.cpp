//
// Created by StevensChew on 17/1/8.
//

#include <iostream>

namespace Katrina {
    namespace spout {
        void SpoutExecutor::StopTask() {
            _needToStop = true;
            base::Executor::StopTask();
        }

        void SpoutExecutor::OnCreate() {
            std::cout << "Start Spout Task" << std::endl;
            _needToStop = false;
            base::OutputCollector outputCollector;
            if (task->GetStrategy == Task::Strategy::Global) {
                outputCollector = base::SpoutOutputCollector(GetTaskName());
            }
            _task->open(outputCollector);
            while (!_needToStop) {
                _task->Execute();
            }
            _task->Close();
        }

        void SpoutExecutor::OnStop() {
            std::cout << "Stop Spout Task" << std::endl;
        }

        void SpoutExecutor::SetCommander(message::MessageCommander *commander) {
            _commander = commander;
        }

        void SpoutExecutor::RandomDestination(
                ::Katrina::spout::SpoutExecutor::SpoutOutputCollector *outputCollector) {
            std::string host;
            int32_t port;
            int32_t destIndex;

            _commander->RandomDestination("spout", _executorIndex, &host, &port, &destIndex);
            outputCollector->SetCommander(
                    new message::MessageCommander(base::NetAddress(host, port), _commander->GetManagerName()));
            outputCollector->SetTaskIndex(destIndex);

        }

        void SpoutExecutor::GroupDestination(::Katrina::spout::SpoutExecutor::SpoutOutputCollector *outputCollector,
                                             int fieldIndex) {
            std::string host;
            int32_t port;
            int32_t destIndex;

            _commander->GroupDestination("spout", _executorIndex, &host, &port, &destIndex, fieldIndex);
            outputCollector->SetCommander(
                    new message::MessageCommander(base::NetAddress(host, port), _commander->GetManagerName()));
            outputCollector->SetTaskIndex(destIndex);
        }
    }
}