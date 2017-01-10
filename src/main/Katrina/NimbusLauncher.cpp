//
// Created by StevensChew on 17/1/8.
//

#include <iostream>
#include <vector>
#include <map>
#include "../../../include/main/Katrina/topology/ITopology.h"
#include "../../../include/main/Katrina/base/NetAddress.h"
#include "../../../include/main/Katrina/base/Node.h"
#include "../../../include/main/Katrina/message/Command.h"
#include "../../../include/main/Katrina/message/NimbusCommander.h"
#include "../../../include/main/Katrina/message/CommandDispatcher.h"
#include "../../../include/main/Katrina/base/NetListener.h"
#include "../../../include/main/Katrina/base/NetConnector.h"

using namespace std;
using namespace Katrina::base;
using namespace Katrina::topology;
using namespace Katrina::bolt;
using namespace Katrina::message;
using namespace Katrina::spout;
using namespace Katrina::net;

const NetAddress NIMBUS_ADDRESS{"127.0.0.1", 6000};
const std::map<std::string, NetAddress> SUPERVISOR_ADDRESSES{
        {"s1", {"127.0.0.1", 7001}}
};

typedef std::vector<std::string> Tasks;
typedef std::map<std::string, int> ExecutorCounts;

const int EXECUTOR_CAPACITY = 3;
const int DEFAULT_SPOUT_EXECUTOR_COUNT = 1;
const int DEFAULT_BOLT_EXECUTOR_COUNT = 1;

static void dispatchTasks(std::map<std::string, Node> &supervisors,
                          std::map<std::string, Tasks> &spoutTasks,
                          std::map<std::string, Tasks> &boltTasks, ITopology *topology) {
    ExecutorCounts neededExecutors;
    for (const auto &pair : topology->GetBolts()) {
        neededExecutors[pair.first] = DEFAULT_BOLT_EXECUTOR_COUNT;
    }
    for (const auto &pair : topology->GetSpouts()) {
        neededExecutors[pair.first] = DEFAULT_SPOUT_EXECUTOR_COUNT;
    }

    for (auto &boltPair : topology->GetBolts()) {
        std::string boltName = boltPair.first;
        std::shared_ptr<IBolt> bolt = boltPair.second;

        if (neededExecutors[boltName] > 0) {
            for (auto &pair : supervisors) {
                std::string supervisorName = pair.first;
                Node &supervisorNode = pair.second;
                NimbusCommander commander(pair.second.GetAddress());
                std::cout << "Dispatch bolt on :" << supervisorName << std::endl;

                Tasks &tasks = boltTasks[supervisorName];
                for (int taskIndex = 0; taskIndex < tasks.size(); taskIndex++) {
                    if (tasks[taskIndex].empty()) {
                        tasks[taskIndex] = boltName;
                        neededExecutors[boltName]--;
                        commander.StartBolt(boltName, taskIndex);

                        if (neededExecutors[boltName] == 0) {
                            break;
                        }
                    }
                }

                if (neededExecutors[boltName] == 0)
                    break;
            }
        }
    }

    for (auto &spoutPair : topology->GetSpouts()) {
        std::string spoutName = spoutPair.first;
        std::shared_ptr<ISpout> spout = spoutPair.second;

        if (neededExecutors[spoutName] > 0) {
            for (auto &pair : supervisors) {
                std::string supervisorName = pair.first;
                Node &supervisorNode = pair.second;

                NimbusCommander commander(pair.second.GetAddress());
                std::cout << "Dispatch spout on:" << supervisorName << std::endl;

                Tasks &tasks = spoutTasks[supervisorName];
                for (int taskIndex = 0; taskIndex != tasks.size(); ++taskIndex) {
                    if (tasks[taskIndex].empty()) {
                        tasks[taskIndex] = spoutName;
                        neededExecutors[spoutName]--;
                        commander.StartSpout(spoutName, taskIndex);

                        if (neededExecutors[spoutName] == 0)
                            break;
                    }
                }
                if (neededExecutors[spoutName] == 0)
                    break;
            }
        }
    }
}

std::pair<Node, int> GetFieldDestination(
        std::map<std::pair<std::string, std::string>, std::pair<Node, int>> &fieldDestinations,
        std::pair<std::string, std::string> fieldPair,
        ITopology *topology,
        std::map<std::string, Node> &supervisors,
        std::map<std::string, Tasks> &spoutTasks,
        std::map<std::string, Tasks> &boltTasks) {
    if (fieldDestinations.find(fieldPair) != fieldDestinations.end()) {
        return fieldDestinations[fieldPair];
    }

    std::string boltName = fieldPair.first;
    std::string field = fieldPair.second;
    auto &network = topology->GetNetwork();
    int destIndex = rand() % tasks.size();

    int currentIndex = 0;
    int taskDestIndex = rand() % DEFAULT_BOLT_EXECUTOR_COUNT;

    std::string hostName;
    for (auto &boltTaskPair : boltTasks) {
        int taskIndex = 0;
        for (auto &taskName : boltTaskPair.second) {
            if (taskName == nextBoltName) {
                if (currentIndex == taskDestIndex) {
                    destIndex = taskIndex;
                    hostName = supervisorName;
                    break;
                }
                currentIndex++;
                taskIndex++;
            }
        }
    }
    Katrina::base::Node node = supervisors[hostName];
    auto result = std::make_pair(node, destIndex);
    fieldDestinations.insert({fieldPair, result});
    return result;
};

int main() {
    ITopology *topology = GetTopology();
    std::map<std::string, Node> supervisors;
    std::map<std::string, Tasks> spoutTasks;
    std::map<std::string, Tasks> boltTasks;
    std::map<std::pair<std::string, std::string>, std::pair<Node, int>> fieldDestinations;

    NetListener netListener(NIMBUS_ADDRESS);
    CommandDispatcher dispatcher;

    dispatcher.OnCommand(Command::Type::Join,
                         [&](Katrina::base::Variants args, std::shared_ptr<TcpConnection> src) -> void {
                             std::string supervisorName = args[0].GetStringValue();
                             Node supervisor(supervisorName, SUPERVISOR_ADDRESSES.at(supervisorName));
                             supervisor.SetStatus(Node::Status::ALIVED);
                             supervisors[supervisorName] = supervisor;

                             spoutTasks[supervisorName] = Tasks(EXECUTOR_CAPACITY);
                             boltTasks[supervisorName] = Tasks(EXECUTOR_CAPACITY);
                             Command command(Command::Type::Response, {
                                     std::string("nimbus")
                             });

                             ByteArray commandBytes = command.ToDataPackage().Serialize();
                             src->Send(commandBytes.data(), commandBytes.size());
                             if (supervisorName == SUPERVISOR_ADDRESSES.size()) {
                                 std::cout << "All Supervisor started" << std::endl;
                                 dispatchTasks(supervisors, spoutTasks, boltTasks, topology);
                             }
                         })
            .OnCommand(Command::Type::Alive,
                       [&](Katrina::base::Variants args, std::shared_ptr<TcpConnection> src) -> void {
                           std::string supervisorName = args[0].GetStringValue();
                           supervisors[supervisorName].Alive();
                           Command command(Command::Type::Response, {
                                   std::string("nimbus")
                           });
                           ByteArray commandBytes = command.ToDataPackage().Serialize();
                           src->Send(commandBytes.data(), commandBytes.size());
                       })
            .OnCommand(Command::Type::RandomDestination, [&](Katrina::base::Variants args,
                                                             std::shared_ptr<TcpConnection> src) {
                std::string supervisorName = args[0].GetStringValue();
                std::string srcType = args[1].GetStringValue();
                int srcIndex = args[2].GetIntValue();

                if (srcType == "spout") {
                    std::string spoutName = spoutTasks[supervisorName][srcIndex];
                    std::string nextBoltName;

                    auto &network = topology->GetNetwork();
                    int destIndex = rand() % tasks.size();
                    int currentIndex = 0;
                    for (auto &taskName : network[spoutName]) {
                        if (destIndex == currentIndex) {
                            destIndex = currentIndex;
                        }
                        nextBoltName = taskName;
                    }
                    int taskDestIndex = rand() % DEFAULT_BOLT_EXECUTOR_COUNT;
                    currentIndex = 0;
                    destIndex = 0;
                    std::string hostName;

                    for (auto &boltTaskPair : boltTasks) {
                        int taskIndex = 0;
                        std::string supervisorName = boltTaskPair.first;
                        for (auto &taskName : boltTaskPair.second) {
                            if (currentIndex == nextBoltName) {
                                if (currentIndex == taskDestIndex) {
                                    destIndex = taskIndex;
                                    hostName = supervisorName;
                                    break;
                                }
                                currentIndex++;
                                taskIndex++;
                            }
                        }
                    }

                    Command command(Command::Type::Response, {
                            std::string("nimbus"),
                            supervisors[hostName].GetAddress().GetHost(),
                            supervisors[hostName].GetAddress().GetPort(),
                            destIndex
                    });

                    ByteArray commandBytes = command.ToDataPackage().Serialize();
                    src->Send(commandBytes.data(), commandBytes.size());
                } else if (srcType == "bolt") {
                    std::string boltName = boltTasks[supervisorName][srcIndex];
                    std::string nextBoltName;
                    auto &network = topology->GetNetwork();
                    int destIndex = rand() % tasks.size();
                    int currentIndex = 0;
                    for (auto &taskName : network[boltName]) {
                        if (destIndex == currentIndex) {
                            destIndex = currentIndex;
                        }
                        nextBoltName = taskName;
                    }

                    int taskDestIndex = rand() % DEFAULT_BOLT_EXECUTOR_COUNT;
                    currentIndex = 0;
                    destIndex = 0;
                    std:
                    string hostName;
                    for (auto &boltTasksPair : boltTasks) {
                        int taskIndex = 0;
                        std::string supervisorName = boltTasksPair.first;
                        for (auto &taskName : boltTasksPair.second) {
                            if (taskName == nextBoltName) {
                                if (currentIndex == taskDestIndex) {
                                    destIndex == taskIndex;
                                    hostName = supervisorName;
                                    break;
                                }
                                currentIndex++;
                                taskIndex++;
                            }
                        }
                    }

                    Command comman(Command::Type::Response, {
                            std::string("nimbus"),
                            supervisors[hostName].GetAddress().GetHost(),
                            supervisors[hostName].GetAddress().GetPort(),
                            destIndex
                    });
                    ByteArray commandBytes = comman.ToDataPackage().Serialize();
                    src->Send(commandBytes.data(), commandBytes.size());
                }
            })
            .OnCommand(Command::Type::GroupDestination,
                       [&](Katrina::base::Variants args, std::shared_ptr<TcpConnection> src) -> void {
                           std::string supervisorName = args[0].GetStringValue();
                           std::string srcType = args[1].GetStringValue();
                           int srcIndex = args[2].GetIntValue();
                           int fieldIndex = args[3].GetIntValue();
                           std::string field;

                           if (srcType == "spout") {
                               std::string spoutName = spoutTasks[supervisorName][srcIndex];
                               std::string field = topology->GetSpouts().at(spoutName)->DeclareFields()[fieldIndex];
                               auto result = GetFieldDestination(fieldDestinations, std::make_pair(spoutName, field));
                               Command command(Command::Type::Response, {
                                       std::string("nimbus"),
                                       result.first.GetAddress().GetHost(),
                                       result.first.GetAddress().GetPort(),
                                       result.second
                               });
                               ByteArray commandBytes = command.ToDataPackage().Serialize();
                               src->Send(commandBytes.data(), commandBytes.size());
                           }
                           else if (srcType == "bolt") {
                               std::string boltName = boltTasks[supervisorName][srcIndex];
                               std::string filed = topology->GetBolts().at(boltName).get()->DeclareFields()[fieldIndex];
                               auto result = GetFieldDestination(fieldDestinations, std::make_pair(boltName, field));

                               Command command(Command::Type::Response, {
                                       std::string("nimbus"),
                                       result.first.GetAddress().GetHost(),
                                       result.first.GetAddress().GetPort(),
                                       result.second
                               });
                               ByteArray commandBytes = command.ToDataPackage().Serialize();
                               src->Send(commandBytes.data(), commandBytes.size());
                           }

                           if (srcType == "bolt") {
                               std::string boltName = boltTasks[supervisorName][srcIndex];
                               std::string nextBoltName;
                               auto &network = topology->GetNetwork();
                               int destIndex = rand() % tasks.size();
                               int currentIndex = 0;

                               for (auto &taskName : network[boltName]) {
                                   if (destIndex == currentIndex)
                                       destIndex = currentIndex;
                                   nextBoltName = taskName;
                               }

                               int taskDestIndex = rand() % DEFAULT_BOLT_EXECUTOR_COUNT;
                               currentIndex = 0;
                               destIndex = 0;
                               std::string hostName;
                               for (auto &boltTaskPair : boltTasks) {
                                   int taskIndex = 0;
                                   std::string supervisorName = boltTaskPair.first;
                                   for (auto &taskName : boltTaskPair.second) {
                                       if (taskName == nextBoltName) {
                                           if (currentIndex == taskDestIndex) {
                                               destIndex = taskIndex;
                                               hostName = supervisorName;
                                               break;
                                           }
                                           currentIndex++;
                                           taskIndex++;
                                       }
                                   }
                               }

                               Command command(Command::Type::Response, {
                                       std::string("nimbus"),
                                       supervisors[hostName].GetAddress().GetHost(),
                                       supervisors[hostName].GetAddress().GetPort(),
                                       destIndex
                               });
                               ByteArray commandByes = command.ToDataPackage().Serialize();
                               src->Send(commandByes.data(), commandByes.size());
                           }
                       });
    netListener.OnData([&](std::shared_ptr<TcpConnection> connection, const char *buffer, int32_t size) -> void {
        ByteArray receiveData(buffer, size);
        DataPackage receivePackage;
        receivePackage.Deserialize(receiveData);
        Command command(receivePackage);
        command.SetSrc(connection);
        dispatcher.Dispatch(command);
    });

    netListener.StartListen();
    return 0;
}










