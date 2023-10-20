cmake_minimum_required(VERSION 3.26)
project(initials)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp
        NamedPipes_fifo/fifo_server.cpp
        NamedPipes_fifo/fifo_client.cpp
        NamedPipes_fifo/RealExampleMQueue/emitter.cpp
        NamedPipes_fifo/RealExampleMQueue/consumer.cpp)
