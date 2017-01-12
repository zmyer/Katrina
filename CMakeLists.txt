cmake_minimum_required(VERSION 3.3)
project(Katrina)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES include/main/Katrina/spout/ISpout.h
        include/main/Katrina/bolt/IBolt.h
        include/main/Katrina/base/Values.h
        include/main/Katrina/message/MessageLoop.h
        include/main/Katrina/message/MessageLoop.h
        include/main/Katrina/message/MessageLoopManager.h
        include/main/Katrina/base/Executor.h
        include/main/Katrina/bolt/BoltExecutor.h
        src/main/Katrina/bolt/BoltExecutor.cpp
        include/main/Katrina/bolt/BoltExecutor.h
        include/main/Katrina/bolt/BoltMessage.h
        include/main/Katrina/message/Message.h
        include/main/Katrina/base/OutputCollector.h
        include/main/Katrina/base/NetConnector.h
        include/main/Katrina/base/NetListener.h
        include/main/Katrina/base/ITask.h
        include/main/Katrina/base/ByteArray.h
        include/main/Katrina/base/DataPackage.h
        include/main/Katrina/base/Fields.h
        include/main/Katrina/base/NetAddress.h
        include/main/Katrina/base/Node.h
        include/main/Katrina/base/Variant.h
        include/main/Katrina/bolt/BaseBatchBolt.h
        include/main/Katrina/bolt/BaseTransactionBolt.h
        include/main/Katrina/bolt/BoltDeclarer.h
        include/main/Katrina/bolt/BoltOutputCollector.h
        include/main/Katrina/bolt/Emitter.h
        include/main/Katrina/bolt/ICommiter.h
        include/main/Katrina/bolt/TransactionAttempt.h
        include/main/Katrina/message/Command.h
        include/main/Katrina/message/CommandDispatcher.h
        include/main/Katrina/message/NimbusCommander.h
        include/main/Katrina/message/SupervisorCommander.h
        include/main/Katrina/spout/Coordinator.h
        include/main/Katrina/topology/ITopology.h
        include/main/Katrina/topology/LocalTopology.h
        include/main/Katrina/topology/SimpleTopology.h
        include/main/Katrina/topology/TopologyBuilder.h
        src/main/Katrina/base/DataPackage.cpp
        src/main/Katrina/base/NetConnector.cpp
        src/main/Katrina/base/NetListener.cpp
        src/main/Katrina/base/OutputCollector.cpp
        src/main/Katrina/bolt/BoltExecutor.cpp src/main/Katrina/bolt/BoltOutputCollector.cpp src/main/Katrina/message/CommandDispathcer.cpp src/main/Katrina/message/MessageLoop.cpp src/main/Katrina/message/NimbusCommander.cpp src/main/Katrina/message/SupervisorCommander.cpp src/main/Katrina/spout/SpoutExecutor.cpp src/main/Katrina/spout/SpoutOutputCollector.cpp include/main/Katrina/spout/SpoutOutputCollector.h src/main/Katrina/topology/SimpleTopology.cpp src/main/Katrina/topology/TopologyBuilder.cpp src/main/Katrina/NimbusLauncher.cpp include/main/Katrina/spout/SpoutExecutor.h deps/donet/include/Donet.h deps/donet/include/Net.h deps/donet/include/DataSink.h deps/donet/include/Bytearray.h deps/donet/include/utils/Exendian.h deps/donet/include/PackageDataSink.h deps/donet/include/Eventqueue.h deps/donet/include/loop.h deps/donet/include/epoll/EpollClient.h deps/donet/include/epoll/EpollServer.h deps/donet/include/IoLoop.h deps/donet/include/Eventqueueloop.h deps/donet/include/epoll/EpollStream.h deps/donet/include/epoll/EpollConnection.h deps/donet/include/epoll/EpollLoop.h deps/donet/include/bsd/Net_bsd.h deps/donet/include/utils/ConcurrentQueue.h deps/donet/include/utils/ThreadPool.h deps/donet/src/Net.cpp deps/donet/src/PackageDataSink.cpp deps/donet/include/http/HttpClient.h deps/donet/include/http/HttpServer.h deps/donet/include/http/HttpContext.h deps/donet/include/http/HttpConnection.h deps/donet/include/http/HttpRequest.h deps/donet/include/http/HttpResponse.h deps/donet/include/http/HttpDataSink.h)
add_executable(Katrina ${SOURCE_FILES})