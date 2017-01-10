//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_SUPERVISORCOMMANDER_H
#define KATRINA_SUPERVISORCOMMANDER_H

#include "../base/NetAddress.h"
#include "../base/Values.h"

namespace Katrina {
    namespace message {
        class SupervisorCommander {
        public:
            SupervisorCommander(const Katrina::base::NetAddress &nimbusAddress,
                                const std::string &supervisorName) :
                    _nimbusAddress(nimbusAddress), _supervisorName(supervisorName) {

            }

            void Connect() {
                if (!_connector.get()) {
                    _connector = std::make_shared<NetConnector>(_nimbusAddress);
                    _connector->Connect();
                }
            }

            void Join();

            void Alive();

            void SendTuple(int taskIndex, const base::Values &values);

            void RandomDestination(const std::string srcType, int srcIndex, std::string *host, int *port,
                                   int *dstIndex);

            void GroupDestination(const std::string srcType, int srcIndex, std::string *host, int *port, int *dstIndex,
                                  int fieldIndex);

            const std::string GetSupervisorName() const {
                return _supervisorName;
            }

        private:
            Katrina::base::NetAddress _nimbusAddress;
            std::string _supervisorName;
            std::shared_ptr <NetConnection> _connector;
        };
    }
}

#endif //KATRINA_SUPERVISORCOMMANDER_H
