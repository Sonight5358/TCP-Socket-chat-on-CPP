cmake_minimum_required(VERSION 3.20)

# CXX project only
project(TCP-Socket-chat-on-CPP LANGUAGES CXX)

# Executables
add_executable(TCPServer src/Server.cpp src/Socket.cpp)
add_executable(TCPClient src/Client.cpp src/Socket.cpp)

# Libs linking to exe
target_link_libraries(TCPServer PRIVATE ws2_32)
target_link_libraries(TCPClient PRIVATE ws2_32)

# Includes
target_include_directories(TCPServer PRIVATE include)
target_include_directories(TCPClient PRIVATE include)