//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_SIMPLETOPOLOGY_H
#define KATRINA_SIMPLETOPOLOGY_H

#include "ITopology.h"

namespace Katrina {
    namespace topology {
        class SimpleTopology : public ITopology {
        public:
            SimpleTopology();

            void SetSpouts(std::map<std::string, std::shared_ptr<spout::ISpout>> spouts) override;

            void SetBolts(std::map<std::string, std::shared_ptr<bolt::IBolt>> bolts) override;

            void SetNetwork(std::map<std::string, std::vector<std::string>> network) override;

            void EmitFrom(const std::string &src, const base::Values &values) override;

            void Start() override;

            virtual const std::map<std::string, std::shared_ptr<spout::ISpout>> &GetSpouts() const override;

            virtual const std::map<std::string, std::shared_ptr<bolt::IBolt>> &GetBolts() const override;

            virtual const std::map<std::string, std::vector<std::string>> &GetNetwork() const override;

            std::map<std::string, std::shared_ptr<spout::ISpout>> &GetSpouts();

            std::map<std::string, std::shared_ptr<bolt::IBolt>> &GetBolts();

            std::map<std::string, std::vector<std::string>> &GetNetwork();

        private:
            template<classs TaskType, class ExecutorType>
            void allocateTask(std::map<std::string, std::shared_ptr<TaskType>> &tasks,
                              std::vector<std::shared_ptr<ExecutorType>> &freeExecutors,
                              std::map<std::string, std::vector<std::shared_ptr<ExecutorType>>> &allocatedExecutor);

            std::map<std::string, std::shared_ptr<spout::ISpout>> _spouts;
            std::map<std::string, std::shared_ptr<bolt::IBolt>> _bolts;
            std::map<std::string, std::vector<std::string>> _network;
        };
    }
}

#endif //KATRINA_SIMPLETOPOLOGY_H















