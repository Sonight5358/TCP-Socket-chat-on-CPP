cmake_minimum_required(VERSION 3.20)

# CXX project only
project(TCP-Socket-chat-on-CPP LANGUAGES CXX)

add_executable(TCPChat src/Main.cpp)

target_link_libraries(TCPChat PRIVATE ws2_32)