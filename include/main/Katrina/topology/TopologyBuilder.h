//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_TOPOLOGYBUILDER_H
#define KATRINA_TOPOLOGYBUILDER_H

#include <iostream>
#include "../spout/ISpout.h"
#include "../bolt/IBolt.h"
#include "SimpleTopology.h"

using namespace std;

namespace Katrina {
    namespace topology {
        class TopologyBuilder {
        public:
            void SetSpout(const std::string &name, spout::ISpout *spout);

            void SetBolt(const std::string &name, bolt::IBolt *bolt, const std::string &prev);

            SimpleTopology *Build();

        private:
            std::map<std::string, std::shared_ptr<spout::ISpout>> _spouts;
            std::map<std::string, std::shared_ptr<bolt::IBolt>> _bolts;
            std::map<std::string, std::vector<std::string>> _network;
        };
    }
}

#endif //KATRINA_TOPOLOGYBUILDER_H
