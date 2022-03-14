cmake_minimum_required(VERSION 3.0)

project(cpp)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

include_directories(src)

set(src_list 
        src/Log.cpp
        src/TimeTool.cpp
        src/FileTool.cpp
        src/AppendFile.cpp
        src/ThreadPool.cpp
        src/Address.cpp
        src/Socket.cpp
        src/System.cpp
        src/Endian.cpp
)
#aux_source_directory(src src)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_library(libs pthread)

add_executable(test_log ./test/test_log ${src_list})
add_executable(test_server ./test/test_server ${src_list})
add_executable(test_client ./test/test_client ${src_list})

target_link_libraries(test_log ${libs})
target_link_libraries(test_server ${libs})
target_link_libraries(test_client ${libs})