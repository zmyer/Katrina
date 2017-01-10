//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_ITOPOLOGY_H
#define KATRINA_ITOPOLOGY_H

#include <iostream>
#include <map>
#include <vector>
#include "../base/Values.h"

using namespace std;

namespace Katrina {
    namespace spout {
        class ISpout;
    }

    namespace bolt {
        class IBolt;
    }

    namespace topology {
        class ITopology {
        public:
            ~ITopology() { }

            virtual void SetSpouts(std::map <std::string, std::shared_ptr<spout::ISpout>> spouts) = 0;

            virtual void SetBolts(std::map <std::string, std::shared_ptr<bolt::IBolt>> bolts) = 0;

            virtual void SetNetwork(std::map <std::string, std::vector<std::string>> network) = 0;

            virtual void EmitFrom(const std::string &src, const base::Values &values) = 0;

            virtual const std::map <std::string, std::shared_ptr<spout::ISpout>> &GetSpouts() const = 0;

            virtual const std::map <std::string, std::shared_ptr<bolt::IBolt>> &GetBolts() const = 0;

            virtual const std::map <std::string, std::vector<std::string>> &GetNetwork() const = 0;

            virtual void Start() = 0;
        };
    }
}

#endif //KATRINA_ITOPOLOGY_H
