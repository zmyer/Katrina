//
// Created by StevensChew on 17/1/8.
//

#include <iostream>
#include "../../../../include/main/Katrina/message/NimbusCommander.h"
#include "../../../../include/main/Katrina/message/Command.h"

using namespace std;
using namespace Katrina::base;

const int DATA_BUFFER_SIZE = 65535;
namespace Katrina {
    namespace message {
        void NimbusCommander::StartSpout(const std::string &spoutName, int executorIndex) {
            Connect();
            Command command(Command::Type::StartSpout, {
                    spoutName, executorIndex
            });

            DataPackage messagePackage = command.ToDataPackage();
            ByteArray message = messagePackage.Serialize();

            char resultBuffer[DATA_BUFFER_SIZE];
            int32_t resultSize = _connector->SendAndReceive(message.data(), message.size(), resultBuffer,
                                                            DATA_BUFFER_SIZE);

            ByteArray result(resultBuffer, resultSize);
            DataPackage resultPackage;
            resultPackage.Deserialize(result);
            command = Command(resultPackage);
            std::cout << command.GetType() << std::endl;
            std::cout << command.GetArg(0).GetStringValue() << std::endl;
        }

        void NimbusCommander::StartBolt(const std::string &boltName, int executorIndex) {
            Connect();
            Command command(Command::Type::StartBolt, {
                    boltName, executorIndex
            });

            DataPackage messagePackage = command.ToDataPackage();
            ByteArray message = messagePackage.Serialize();

            char resultBuffer[DATA_BUFFER_SIZE];
            int32_t resultSize = _connector->SendAndReceive(message.data, message.size(), resultBuffer,
                                                            DATA_BUFFER_SIZE);
            ByteArray result(resultBuffer, resultSize);
            DataPackage resultPackage;
            resultPackage.Deserialize(result);
            command = Command(resultPackage);

            std::cout << command.GetType() << std::endl;
            std::cout << command.GetArg(0).GetStringValue() << std::endl;
        }
    }
}










