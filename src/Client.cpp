#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define DEFAULT_BUFLEN 1024

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <iostream>

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
	SOCKET ConnectionSocket = INVALID_SOCKET;
	ConnectionSocket = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP, auto protocol

	// If socket was not created
	if (ConnectionSocket == INVALID_SOCKET)
	{
		std::cout << "Client socket was not created :/" << '\n';

		WSACleanup();
		return 1;
	}

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

		closesocket(ConnectionSocket);
		WSACleanup();
		return 1;
	}

	// Connection to server
	Result = connect(ConnectionSocket, (sockaddr*)&ServerAddr, sizeof(ServerAddr)); 

	// If connection failed
	if (Result == SOCKET_ERROR)
	{
		std::cout << "Connection failed///" << '\n';

		closesocket(ConnectionSocket);
		WSACleanup();
		return 1;
	}

	// Message buffer
	char buffer[DEFAULT_BUFLEN];
	int buflen = DEFAULT_BUFLEN;

	while (true)
	{
		// Send
		std::cin.getline(buffer, DEFAULT_BUFLEN);

		// Send message from client on enter
		Result = send(ConnectionSocket, buffer, strlen(buffer), 0);

		// If cant send
		if (Result == SOCKET_ERROR)
		{
			std::cout << "Not sent." << '\n';
			closesocket(ConnectionSocket);
			WSACleanup();
			return 1;
		}

		// Receive message from client (blocking fuction)
		Result = recv(ConnectionSocket, buffer, buflen, 0); // Connection socket, buffer, lenght of buffer, advanced receiving option flag

		// If cant recieve
		if (Result == SOCKET_ERROR)
		{
			std::cout << "Not received." << '\n';
			closesocket(ConnectionSocket);
			WSACleanup();
			return 1;
		}
	}

	// In console
	std::cout << "Client: ";
	std::cout.write(buffer, Result);
	std::cout << '\n';

	// Close socket
	closesocket(ConnectionSocket);

	// WS2_32 terminate
	WSACleanup();
	return 0;
}