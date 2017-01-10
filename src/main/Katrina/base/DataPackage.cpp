//
// Created by StevensChew on 17/1/8.
//

#include <memory>
#include <map>
#include "../../../../include/main/Katrina/base/DataPackage.h"
#include "../../../../include/main/Katrina/base/Variant.h"

namespace Katrina {
    namespace base {
        std::map<int8_t, std::shared_ptr<Writable>> Writables = {
                {0, std::shared_ptr<Writable>(new IntWritable)},
                {3, std::shared_ptr<Writable>(new StringWritable)}
        };

        std::map<Variant::Type, int8_t> Variant::TypeCodes = {
                {Variant::Type::INTEGER, 0},
                {Variant::Type::STRING,  3}
        };

        std::map<Variant::Type, std::string> Variant::TypeNames = {
                {Variant::Type::INVALID, "Invalid"},
                {Variant::Type::INTEGER, "Integer"},
                {Variant::Type::BOOLEAN, "Boolean"},
                {Variant::Type::FLOAT,   "Float"},
                {Variant::Type::STRING,  "String"}

        };
    }
}
