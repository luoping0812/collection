cmake_minimum_required(VERSION 3.0)

project(cpp)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

include_directories(src)
include_directories(src/utils)
include_directories(src/net)

set(src_list 
        src/utils/Log.cpp
        src/utils/System.cpp
        src/utils/TimeTool.cpp
        src/utils/FileTool.cpp
        src/utils/AppendFile.cpp
        src/utils/ThreadPool.cpp
        src/net/Address.cpp
        src/net/Socket.cpp
        src/net/Endian.cpp
        src/net/Epoll.cpp
        src/net/Acceptor.cpp
        src/net/Connection.cpp
        src/net/Channel.cpp
        src/net/EventLoop.cpp
        src/net/TcpServer.cpp
)
#aux_source_directory(src src)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_library(libs pthread)

add_executable(test_log ./test/test_log ${src_list})
add_executable(test_server ./test/test_server ${src_list})
add_executable(test_client ./test/test_client ${src_list})
add_executable(test_epoll ./test/test_epoll ${src_list})

target_link_libraries(test_log ${libs})
target_link_libraries(test_server ${libs})
target_link_libraries(test_client ${libs})
target_link_libraries(test_epoll ${libs})