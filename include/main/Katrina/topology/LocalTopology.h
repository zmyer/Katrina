//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_LOCALTOPOLOGY_H
#define KATRINA_LOCALTOPOLOGY_H

#include "ITopology.h"

using namespace std;

namespace Katrina {
    namespace topology {
        class LocalTopology {
        public:
            LocalTopology() { }

            void Submit(const std::string &name, std::shared_ptr <ITopology> topology) {
                _topologies[name] = topology;
                topology->Start();
            }

        private:
            std::map <std::string, std::shared_ptr<ITopology>> _topologies;
        };
    }
}

#endif //KATRINA_LOCALTOPOLOGY_H
