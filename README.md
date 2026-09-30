# TCP Socket Chat in C++

A small console chat built on raw sockets (Winsock2). It consists of a server and a client and was written to practice C++ and CMake. It currently has a console-only version.

## Features

- Separate `TCPServer` and `TCPClient` executables
- Socket wrapper for IPv4 and IPv6
- Plain TCP over Winsock2, no third-party dependencies
- Retry mechanism for failed operations
- Multithreaded message receiving
- Graceful connection shutdown with /exit
- Handling of partial `send()` operations
- CMake-based build system

## Requirements

- **OS:** Windows (links against `ws2_32`)
- **Compiler:** any C++17-capable one (MSVC, MinGW-w64)
- **CMake:** 3.20 or newer

## Build

```bash
git clone https://github.com/Sonight5358/TCP-Socket-chat-on-CPP.git
cd TCP-Socket-chat-on-CPP

cmake -S . -B build
cmake --build build --config Release
```

## Usage

1. Start the server first:

   ```bash
   ./TCPServer
   ```

2. In another terminal, start the client:

   ```bash
   ./TCPClient
   ```

## Roadmap

- Qt/QML GUI
- Multiple clients at once
- Nicknames and timestamps
- Linux support (POSIX sockets)

## Resources

Built while studying the [Microsoft Winsock documentation](https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2) and the [CMake documentation](https://cmake.org/cmake/help/latest/).