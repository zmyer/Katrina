//
// Created by StevensChew on 17/1/8.
//


#include "../../../../include/main/Katrina/bolt/IBolt.h"
#include "../../../../include/main/Katrina/spout/ISpout.h"
#include "../../../../include/main/Katrina/topology/TopologyBuilder.h"

namespace Katrina {
    namespace topology {
        void TopologyBuilder::SetSpout(const std::string &name, spout::ISpout *spout) {
            _spouts[name] = std::shared_ptr<spout::ISpout>(spout);
        }

        void TopologyBuilder::SetBolt(const std::string &name, bolt::IBolt *bolt, const std::string &prev) {
            _bolts[name] = std::shared_ptr<bolt::IBolt>(bolt);
            auto destinations = _network.find(prev);
            if (destinations == _network.end()) {
                destinations = _network.insert(make_pair(prev, std::vector<std::string>())).first;
            }
            destinations->second.push_back(name);
        }

        SimpleTopology *TopologyBuilder::Build() {
            SimpleTopology *topology = new SimpleTopology;
            topology->SetSpouts(_spouts);
            topology->SetBolts(_bolts);
            topology->SetNetwork(_network);

            return topology;
        }
    }
}
