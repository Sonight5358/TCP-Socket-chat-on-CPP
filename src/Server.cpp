#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define DEFAULT_BUFLEN 1024

#include <winsock2.h>
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
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP, auto protocol

	// If socket was not created
	if (ListenSocket == INVALID_SOCKET)
	{
		std::cout << "Server socket was not created :/" << '\n';

		WSACleanup();
		return 1;
	}

	// Struct with server info
	sockaddr_in ServAddr{};
	ServAddr.sin_family = AF_INET;			// IPv4
	ServAddr.sin_port = htons(5358);		// Converts to network byte order
	ServAddr.sin_addr.s_addr = INADDR_ANY;  // .sin_addr - struct with IP, .s_addr (unsigned long) - field of the .sin_addr for IP, INADDR_ANY - 0.0.0.0 (any address basically)

	// Bind Ip and port with this exact socket
	Result = bind(ListenSocket, (sockaddr*)&ServAddr, sizeof(ServAddr)); // Socket descriptor, struct with server info, size of struct

	// If binding failed
	if (Result == SOCKET_ERROR)
	{
		std::cout << "Binding failed..." << '\n';

		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Listening
	Result = listen(ListenSocket, SOMAXCONN); // Socket descriptor, max length of pending connection queue

	// If listening failed
	if (Result == SOCKET_ERROR)
	{
		std::cout << "Listening failed..." << '\n';

		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Info about client address
	sockaddr_in ClientAddr{};

	int ClientAddrSize = sizeof(ClientAddr);

	// Accept of incoming connection attempt and saving client socket
	SOCKET ConnectionSocket = accept(ListenSocket, (sockaddr*)&ClientAddr, &ClientAddrSize); // accept() will populate second field with client address

	// If not accepted
	if (ConnectionSocket == INVALID_SOCKET)
	{
		std::cout << "Not accepted" << '\n';
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Message buffer
	char buffer[DEFAULT_BUFLEN];
	int buflen = DEFAULT_BUFLEN;

	// Receive message from client (blocking fuction)
	Result = recv(ConnectionSocket, buffer, buflen, 0); // Client socket, buffer, lenght of buffer, advanced receiving option flag

	// If cant recieve
	if (Result == SOCKET_ERROR)
	{
		std::cout << "Not received." << '\n';
		closesocket(ConnectionSocket);
		WSACleanup();
		return 1;
	}

	// Close socket
	closesocket(ListenSocket);

	// WS2_32 terminate
	WSACleanup();
	return 0;
}