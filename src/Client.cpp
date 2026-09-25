#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define DEFAULT_BUFLEN 1024

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <iostream>
#include <thread>
#include "Socket.h"

// Receive message from server (blocking fuction) in a separate thread
void ReceiveThread(Socket& ConnectionSocket)
{
	// Message buffer
	char buffer[DEFAULT_BUFLEN];

	while (true)
	{
		int Result;
		Result = ConnectionSocket.Recv(buffer, 0);

		if (Result == 0)
		{
			std::cout << "Connection closed." << '\n';
			return;
		}

		// In console
		std::cout << "Server: ";
		std::cout.write(buffer, Result);
		std::cout << '\n';
	}
}

int main()
{	
	// Info about Winsock init
	WSADATA WsaData;
	int Result;
	Result = WSAStartup(MAKEWORD(2, 2), &WsaData);

	// If Winsock init failed
	if (Result != 0)
	{
		std::cout << "Startup failed :(" << '\n';

		return 1;
	}

	// Socket
	Socket ConnectionSocket;

	// Struct with server info
	sockaddr_in ServerAddr{};
	ServerAddr.sin_family = AF_INET;		// IPv4
	ServerAddr.sin_port = htons(5358);		// Converts to network byte order

	// Converting string address to binary
	Result = inet_pton(AF_INET, "127.0.0.1", &ServerAddr.sin_addr);

	// If converting failed
	if (Result != 1)
	{
		std::cout << "pton failed!" << '\n';
		WSACleanup();
		return 1;
	}

	// Connection to server
	ConnectionSocket.Connect(ServerAddr); 

	// Message buffer
	char buffer[DEFAULT_BUFLEN];

	// Thread for receiving messages from server
	std::thread Thread1(ReceiveThread, ConnectionSocket);

	while (true)
	{
		// Send
		std::cin.getline(buffer, DEFAULT_BUFLEN);

		// Send message from client on enter
		ConnectionSocket.Send(buffer, 0);
	}

	// Wait for the new thread to finish
	Thread1.join();

	// WS2_32 terminate
	WSACleanup();
	return 0;
}