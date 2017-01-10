//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_NIMBUSCOMMANDER_H
#define KATRINA_NIMBUSCOMMANDER_H

#include "../base/NetAddress.h"

namespace Katrina {
    namespace message {
        class NimbusCommander {
        public:
            NimbusCommander(const Katrina::base::NetAddress &supervisorAddress) :
                    _supervisorAddress(supervisorAddress) {

            }

            void Connect() {
                if (!_connector.get()) {
                    _connector = std::make_shared<NetConnector>(_supervisorAddress);
                    _connector->Connect();
                }
            }

            void StartSpout(const std::string &spoutName, int executorIndex);

            void StartBolt(const std::string &boltName, int executorIndex);

        private:
            Katrina::base::NetAddress _supervisorAddress;
            std::shared_ptr <NetConnector> _connector;
        };
    }
}

#endif //KATRINA_NIMBUSCOMMANDER_H
