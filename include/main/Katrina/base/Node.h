//
// Created by StevensChew on 17/1/7.
//

#ifndef KATRINA_NODE_H
#define KATRINA_NODE_H

#include <iostream>
#include "NetAddress.h"

using namespace std;

namespace Katrina {
    namespace base {
        class Node {
        public:
            enum class Status {
                DEAD,
                ALIVED
            };

            Node() : _address("", 0), _status(Status::DEAD) {

            }

            Node(std::string name, const NetAddress &address) :
                    _name(name), _address(address), _status(Status::DEAD) {

            }

            const std::string &GetName() const {
                return _name;
            }

            void SetName(const std::string &name) {
                _name = name;
            }

            const NetAddress &GetAddress() const {
                return _address;
            }

            void SetAddress(const NetAddress &address) {
                _address = address;
            }

            Status GetStatus() const {
                return _status;
            }

            void SetStatus(Status status) {
                _status = status;
            }

            void Alive() {
                _lastLiveTime = time_t(0);
            }

            Status UpdateStatus() {
                time_t currentTime = 0;
                if (_lastLiveTime - currentTime > 9) {
                    _status = Status::DEAD;
                }
                return _status;
            }

        private:
            std::string _name;
            NetAddress _address;
            Status _status;
            time_t _lastLiveTime;
        };
    }
}
#endif //KATRINA_NODE_H
