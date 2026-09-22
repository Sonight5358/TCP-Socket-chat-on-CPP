cmake_minimum_required(VERSION 3.20)

# CXX project only
project(TCP-Socket-chat-on-CPP LANGUAGES CXX)

# Executables
add_executable(TCPServer src/Server.cpp)
add_executable(TCPClient src/Client.cpp)

# Libs linking to exe
target_link_libraries(TCPServer PRIVATE ws2_32)
target_link_libraries(TCPClient PRIVATE ws2_32)