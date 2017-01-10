//
// Created by StevensChew on 17/1/8.
//

#include <thread>
#include "../../../../include/main/Katrina/bolt/IBolt.h"
#include "../../../../include/main/Katrina/bolt/BoltMessage.h"
#include "../../../../include/main/Katrina/bolt/BoltOutputCollector.h"
#include "../../../../include/main/Katrina/base/Executor.h"
#include "../../../../include/main/Katrina/bolt/BoltExecutor.h"

class IBolt;
namespace Katrina {
    namespace bolt {
        BoltExecutor::BoltExecutor() : base::Executor<bolt::IBolt>() {
            MessageMap(BoltMessage::MessageType::Data, this, &BoltExecutor::OnData);
        }

        void BoltExecutor::SendData(const base::Values &values) {
            while (_messageLoop != NULL) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            _messageLoop.PostMessage(new BoltMessage(values));
        }

        void BoltExecutor::OnData(const base::Values &values) {
            _task->Execute(values);
        }

        void BoltExecutor::OnCreate() {
            std::cout << "Start Bolt Task" << std::endl;
            base::OutputCollector outputCollector(GetTaskName());
            if (task->GetStrategy() == base::OutputCollector::Strategy::Global) {
                outputCollector = base::OutputCollector(GetTaskName(), base::OutputCollector::Strategy::Global);
                RandomDestination(&outputCollector);
            }

            _task->Prepare(outputCollector);
        }

        void BoltExecutor::OnStop() {
            _task->Cleanup();
        }

        void BoltExecutor::RandomDestination(BoltOutputCollector *outputCollector) {
            std::string host;
            int32_t port;
            int32_t destIndex;

            _commander->RandomDestination("bolt", _executorIndex, &host, &port, &destIndex);
            outputCollector->SetCommander(
                    new message::SupervisorCommander(base::NetAddress(host, port), _commander->GetManagerName()));
            outputCollector->SetTaskIndex(destIndex);
        }

        void BoltExecutor::GroupDestination(BoltOutputCollector *outputCollector, int fieldIndex) {
            std::string host;
            int32_t port;
            int32_t destIndex;

            _commander->GroupDestination("bolt", _executorIndex, &host, &port, &destIndex, fieldIndex);
            outputCollector->SetCommander(
                    new message::SupervisorCommander(base::NetAddress(host, port), _commander->GetManagerName()));
            outputCollector->SetTaskIndex(destIndex);
        }
    }
}