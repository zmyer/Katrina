//
// Created by StevensChew on 17/1/8.
//

#include "../../../../include/main/Katrina/topology/SimpleTopology.h"

namespace Katrina {
    namespace topology {
        SimpleTopology::SimpleTopology() {

        }

        void SimpleTopology::SetSpouts(std::map<std::string, std::shared_ptr<spout::ISpout>> spouts) {
            _spouts = spouts;
        }

        void SimpleTopology::SetNetwork(std::map<std::string, std::vector<std::string>> network) {
            _network = network;
        }

        void SimpleTopology::EmitFrom(const std::string &src, const base::Values &values) {

        }

        void SimpleTopology::Start() {

        }

        const std::map<std::string, std::shared_ptr<spout::ISpout>> &SimpleTopology::GetSpouts() const {
            return _spouts;
        }

        const std::map<std::string, std::shared_ptr<bolt::IBolt>> &SimpleTopology::GetBolts() const {
            return _bolts;
        }

        const std::map<std::string, std::vector<std::string>> &SimpleTopology::GetNetwork() const {
            return _network;
        }

        std::map<std::string, std::shared_ptr<spout::ISpout>> &SimpleTopology::GetSpouts() {
            return _spouts;
        }

        std::map<std::string, std::shared_ptr<bolt::IBolt>> &SimpleTopology::GetBolts() {
            return _bolts;
        }

        std::map<std::string, std::vector<std::string>> &SimpleTopology::GetNetwork() {
            return _network;
        }

        template<class TaskType, class ExecutorType>
        void SimpleTopology::allocateTask(std::map<std::string, std::shared_ptr<TaskType>> &tasks,
                                          std::vector<std::shared_ptr<ExecutorType>> &freeExecutors,
                                          std::map<std::string, std::vector<std::shared_ptr<ExecutorType>>> &allocatedExecutor) {

        }
    }
}