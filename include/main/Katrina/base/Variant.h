//
// Created by StevensChew on 17/1/7.
//

#ifndef KATRINA_VARIANT_H
#define KATRINA_VARIANT_H

namespace Katrina {
    namespace base {
        class Variant {
        public:
            enum class Type {
                INVALID,
                INTEGER,
                BOOLEAN,
                FLOAT,
                STRING
            };

            static std::map<Type, int8_t> TypeCodes;
            static std::map<Type, std::string> TypeNames;

            Variant() : _type(Type::INVALID) {

            }

            Variant(int32_t intValue) : _type(Type::INTEGER), _intValue(intValue) {

            }

            Variant(const std::string &stringValue) : _type(Type::STRING), _stringValue(stringValue) {

            }

            ~Variant() { }

            Variant(const Variant &variant) : _type(variant._type) {
                if (_type == Type::INTEGER) {
                    _intValue = variant._intValue;
                } else if (_type == Type::STRING) {
                    _stringValue = variant._stringValue;
                }
            }

            const Variant &operator=(const Variant &variant) {
                _type = variant._type;
                if (_type == Type::INTEGER) {
                    _intValue = variant._intValue;
                } else if (_type == Type::STRING) {
                    _stringValue = variant._stringValue;
                }
                return *this;
            }

            Type GetType() const {
                return _type;
            }

            int32_t GetIntValue() const {
                if (_type == Type::INVALID) {
                    std::cerr << "INVALID";
                }
                if (_type == Type::INTEGER) {
                    return _intValue;
                }
                throw "Type mismatched";
            }

            void SetIntValue(int32_t value) {
                _type = Type::INTEGER;
                _intValue = value;
            }

            std::string GetStringValue() const {
                if (_type == Type::INVALID) {
                    std::cerr << "Invalid";
                }
                if (_type == Type::STRING) {
                    return _stringValue;
                }
                throw "Type mismatched";
            }

            void SetStringValue(const std::string &value) {
                _type = Type::STRING;
                _stringValue = value;
            }

        private:
            Type _type;
            union {
                int32_t _intValue;
                bool _boolValue;
                float _floatValue;
            };
            std::string _stringValue;
        };

        typedef std::vector<Variant> Variants;
    }
}

#endif //KATRINA_VARIANT_H
