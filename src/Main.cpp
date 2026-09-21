#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <windows.h>

#include <iostream>

int main()
{	
	// Info about Winsock init
	WSADATA WsaData;
	int Result;

	Result = WSAStartup(MAKEWORD(2, 2), &WsaData);
	if (Result != 0)
	{
		std::cout << "Startup failed :(" << '\n';

		return 1;
	}

	// Socket
	SOCKET ServerSocket = INVALID_SOCKET;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP, auto protocol

	// If socket was not created
	if (ServerSocket == INVALID_SOCKET)
	{
		std::cout << "Socket was not created :/" << '\n';

		WSACleanup();
		return 1;
	}

	// Struct with server info
	sockaddr_in ServAddr{};
	ServAddr.sin_family = AF_INET;			// IPv4
	ServAddr.sin_port = htons(5358);		// Converts to network byte order
	ServAddr.sin_addr.s_addr = INADDR_ANY;  // .sin_addr - struct with IP, .s_addr (unsigned long) - field of the .sin_addr for IP, INADDR_ANY - 0.0.0.0 (any address basically)

	// Bind Ip and port with this exact socket
	Result = bind(ServerSocket, (sockaddr*)&ServAddr, sizeof(ServAddr)); // Socket descriptor, struct with server info, size of struct


	if (Result != 0)
	{
		std::cout << "Binding failed..." << '\n';

		closesocket(ServerSocket);
		WSACleanup();
		return 1;
	}


	// Close socket
	closesocket(ServerSocket);

	// WS2_32 terminate
	WSACleanup();
	return 0;
}