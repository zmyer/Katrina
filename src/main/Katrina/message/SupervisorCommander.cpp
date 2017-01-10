//
// Created by StevensChew on 17/1/8.
//

#include "../../../../include/main/Katrina/message/SupervisorCommander.h"
#include "../../../../include/main/Katrina/message/Command.h"
#include "../../../../include/main/Katrina/base/Values.h"

const int DATA_BUFFER_SIZE = 65535;

namespace Katrina {
    namespace message {
        void SupervisorCommander::Join() {
            Connect();
            Command command(Command::Type::Join, {
                    _supervisorName
            });

            DataPackage messagePackage = command.ToDataPackage();
            ByteArray message = messagePackage.Serialize();

            char resultBuffer[DATA_BUFFER_SIZE];
            int32_t resultSize =
                    _connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);
            ByteArray result(resultBuffer, resultSize);
            DataPackage resultPackage;
            resultPackage.Deserialize(result);
            command = Command(resultPackage);

            std::cout << command.GetType() << std::endl;
            std::cout << command.GetArg(0).GetStringValue() << std::endl;
        }

        void SupervisorCommander::Alive() {
            Connect();
            Command command(Command::Type::Alive, {
                    _supervisorName
            });
            DataPackage messagePackage = command.ToDataPackage();
            ByteArray message = messagePackage.Serialize();

            char resultBuffer[DATA_BUFFER_SIZE];
            int32_t resultSize =
                    _connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);
            ByteArray result(resultBuffer, resultSize);
            DataPackage resultPackage;
            resultPackage.Deserialize(result);
            command = Command(resultPackage);

        }

        void SupervisorCommander::SendTuple(int taskIndex, const base::Values &values) {
            Connect();
            base::Variants args = {
                    _supervisorName,
                    _taskIndex
            };

            for (const base::Value &value : values) {
                args.pop_back(value.ToVariant());
            }

            Command command(Command::Type::Data, args);
            DataPackage messagePackage = command.ToDataPackage();
            ByteArray message = messagePackage.Serialize();

            char resultBuffer[DATA_BUFFER_SIZE];
            int32_t resultSize =
                    _connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);
            ByteArray result(resultBuffer, resultSize);
            DataPackage resultPackage;
            command = Command(resultPackage);

            std::cout << command.GetType() << std::endl;
            std::cout << command.GetArg(0).GetStringValue() << std::endl;
        }

        void SupervisorCommander::RandomDestination(const std::string srcType, int srcIndex, std::string *host,
                                                    int *port, int *dstIndex) {
            Connect();
            Command command(Command::Type::RandomDestination, {
                    _supervisorName,
                    srcType,
                    srcIndex
            });

            DataPackage messagePackage = command.ToDataPackage();
            ByteArray message = messagePackage.Serialize();

            char resultBufffer[DATA_BUFFER_SIZE];
            int32_t resultSize =
                    _connector->SendAndReceive(message.data(), message.size(), resultBufffer, DATA_BUFFER_SIZE);
            ByteArray result(resultBufffer, resultSize);
            DataPackage resultPackage;
            resultPackage.Deserialize(result);
            command = Command(resultPackage);

            *host = command.GetArg(1).GetStringValue();
            *port = command.GetArg(2).GetIntValue();
            *dstIndex = command.GetArg(3).GetIntValue();
        }

        void SupervisorCommander::GroupDestination(const std::string srcType, int srcIndex, std::string *host,
                                                   int *port, int *dstIndex, int fieldIndex) {
            Connect();
            Command command(Command::Type::RandomDestination, {
                    _supervisorName,
                    srcType,
                    srcIndex,
                    fieldIndex
            });

            DataPackage messagePackage = command.ToDataPackage();
            ByteArray message = messagePackage.Serialize();

            char resultBuffer[DATA_BUFFER_SIZE];
            int32_t resultSize =
                    _connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);
            ByteArray result(resultBuffer, resultSize);
            DataPackage resultPackage;
            resultPackage.Deserialize(result);
            command = Command(resultPackage);

            *host = command.GetArg(1).GetStringValue();
            *port = command.GetArg(2).GetIntValue();
            *dstIndex = command.GetArg(3).GetIntValue();
        }

    }
}
