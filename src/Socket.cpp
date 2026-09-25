#include "Socket.h"

Socket::Socket(int af, int type, int protocol)
{
	SocketDesc = socket(af, type, protocol);

	// If socket was not created
	if (SocketDesc == INVALID_SOCKET)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}
}

// Constructor for already existing socket descriptor
Socket::Socket(SOCKET createsock) : SocketDesc(createsock) {}

// Destructor
Socket::~Socket()
{
	closesocket(SocketDesc);
}

// Bind Ip and port with this exact socket (IPv4)
void Socket::Bind(const sockaddr_in& name) // Struct with server info
{
	// If binding failed
	if (bind(SocketDesc, (sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}
}

// Bind Ip and port with this exact socket (IPv6)
void Socket::Bind(const sockaddr_in6& name) // Struct with server info
{
	// If binding failed
	if (bind(SocketDesc, (sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}
}

// Listening
void Socket::Listen(int backlog)
{
	// If listening failed
	if (listen(SocketDesc, backlog) == SOCKET_ERROR) // Socket descriptor, max length of pending connection queue)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}
}

// Accept (IPv4)
Socket Socket::Accept(sockaddr_in& name)
{
	int addrlen = sizeof(name);

	// New socket class
	SOCKET newsock = INVALID_SOCKET;

	newsock = accept(SocketDesc, (sockaddr*)&name, &addrlen);

	// If not accepted
	if (newsock == INVALID_SOCKET)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}

	/*Socket sock(newsock);
	return sock;*/
	
	return Socket(newsock);

}

// Accept (IPv6)
Socket Socket::Accept(sockaddr_in6& name)
{
	int addrlen = sizeof(name);

	// New socket class
	SOCKET newsock = INVALID_SOCKET;

	newsock = accept(SocketDesc, (sockaddr*)&name, &addrlen);

	// If not accepted
	if (newsock == INVALID_SOCKET)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}

	/*Socket sock(newsock);
	return sock;*/

	return Socket(newsock);
}

// Connect (IPv4)
void Socket::Connect(const sockaddr_in& name)
{
	// If connection failed
	if (connect(SocketDesc, (sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}
}

// Connect (IPv6)
void Socket::Connect(const sockaddr_in6& name)
{
	// If connection failed
	if (connect(SocketDesc, (sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}
}

// Send message
void Socket::Send(const char* buf, int flag)
{
	// If cant send
	if (send(SocketDesc, buf, strlen(buf), flag) == SOCKET_ERROR)
	{
		throw std::runtime_error(std::to_string(WSAGetLastError()));
	}
}

// Receive in a template in .h