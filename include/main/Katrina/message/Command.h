//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_COMMAND_H
#define KATRINA_COMMAND_H

#include "../base/Variant.h"
#include "../base/DataPackage.h"

namespace Katrina {
    namespace message {
        class Command {
        public:
            class Type {
            public:
                enum Values {
                    Invaild = 0,
                    Join = 1,
                    Alive = 2,
                    Leave = 3,
                    StartTopology = 4,
                    ShutdownTopology = 5,
                    StartSpout = 7,
                    StartBolt = 8,
                    StopBolt = 9,
                    RandomDestination = 10,
                    GroupDestination = 11,
                    Response = 254,
                    Data = 255
                };
            };

            Command() : _type(Command::Type::Invaild) {

            }

            Command(Command::Type::Values type, const Katrina::base::Variants &args) :
                    _type(type), _args(args) { }

            Command(const Katrina::base::DataPackage &dataPackage) {
                const Katrina::base::Variants variants = dataPackage.GetVariants();
                _type = Command::Type::Values(variants[0].GetIntValue());
                _args = variants;
                _args.erase(_args.begin());
            }

            Katrina::base::DataPackage ToDataPackage() const {
                Katrina::base::DataPackage dataPackage;
                dataPackage.AddVariant(int(_type));
                for (auto arg : _args) {
                    dataPackage.AddVariant(arg);
                }
                return dataPackage;
            }

            Command::Type::Values GetType() const {
                return _type;
            }

            void SetType(Command::Type::Values type) {
                _type = type;
            }

            const Katrina::base::Variant &GetArg(int index) const {
                return _args[index];
            }

            Katrina::base::Variant &GetArg(int index) {
                return _args[index];
            }

            const Katrina::base::Variants &GetArgs() const {
                return _args;
            }

            void SetArgs(const Katrina::base::Variants &args) {
                _args = args;
            }

            void PushArg(const Katrina::base::Variant &arg) {
                _args.push_back(arg);
            }

            const Katrina::base::Variant PopArg() {
                Katrina::base::Variant arg = _args.back();
                _args.pop_back();
            }

            std::shared_ptr<TcpConnection> GetSrc() const {
                return _src;
            }

            void SetSrc(std::shared_ptr<TcpConnection> src) {
                _src = src;
            }

        private:
            Command::Type::Values _type;
            Katrina::base::Variants _args;
            std::shared_ptr<TcpConnection> _src;
        };
    }
}

#endif //KATRINA_COMMAND_H
