#include "WindowsSocketRaii.h"

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

namespace Net
{
	WindowsSocketRaii::WindowsSocketRaii(int domain, int type, int protocol)
		: m_socket{ socket(domain, type, protocol) }
	{
		if (m_socket == INVALID_SOCKET)
		{
			throw GetError();
		}
	}

	WindowsSocketRaii::WindowsSocketRaii(WindowsSocketRaii&& socket) noexcept
		: m_socket{ socket.Get() }
	{
		socket.m_socket = -1;
	}

	WindowsSocketRaii& WindowsSocketRaii::operator=(WindowsSocketRaii&& socket) noexcept
	{
		m_socket = socket.Get();
		socket.m_socket = -1;
		return *this;
	}

	WindowsSocketRaii::~WindowsSocketRaii()
	{
		if (m_socket != -1)
		{
			closesocket(m_socket);
		}
	}

	unsigned long long WindowsSocketRaii::Get() const noexcept
	{
		return m_socket;
	}

	WindowsSocketError WindowsSocketRaii::GetError() const noexcept
	{
		switch (WSAGetLastError())
		{
		case WSANOTINITIALISED: return WindowsSocketError::WinsockNotInitialized;
		case WSAENETDOWN: return WindowsSocketError::NetworkSystemDown;
		case WSAEAFNOSUPPORT: return WindowsSocketError::AddressFamilyNotSupported;
		case WSAEINPROGRESS: return WindowsSocketError::OperationInProgress;
		case WSAEMFILE: return WindowsSocketError::NoMoreDescriptorsAvaliable;
		case WSAEINVAL: return WindowsSocketError::InvalidArgument;
		case WSAEINVALIDPROVIDER: return WindowsSocketError::InvalidProvider;
		case WSAEINVALIDPROCTABLE: return WindowsSocketError::InvalidProcedureTable;
		case WSAENOBUFS: return WindowsSocketError::NoBuffers;
		case WSAEPROTONOSUPPORT: return WindowsSocketError::NoProtocolSupport;
		case WSAEPROTOTYPE: return WindowsSocketError::Prototype;
		case WSAEPROVIDERFAILEDINIT: return WindowsSocketError::ProviderFailedInit;
		case WSAESOCKTNOSUPPORT: return WindowsSocketError::SocketTypeSupported;
		default: return WindowsSocketError::Unknown;
		}
	}

	std::string GetErrorDescription(WindowsSocketError error) noexcept
	{
		switch(error)
		{
		case WindowsSocketError::WinsockNotInitialized: return "A successful WSAStartup call must occur before using this function.";
		case WindowsSocketError::NetworkSystemDown: return "The network subsystem or the associated service provider has failed.";
		case WindowsSocketError::AddressFamilyNotSupported: return "The specified address family is not supported. For example, an application tried to create a socket for the AF_IRDA address family but an infrared adapter and device driver is not installed on the local computer.";
		case WindowsSocketError::OperationInProgress: return "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
		case WindowsSocketError::NoMoreDescriptorsAvaliable: return "No more socket descriptors are available.";
		case WindowsSocketError::InvalidArgument: return "An invalid argument was supplied. This error is returned if the af parameter is set to AF_UNSPEC and the type and protocol parameter are unspecified.";
		case WindowsSocketError::InvalidProvider: return "The service provider returned a version other than 2.2.";
		case WindowsSocketError::InvalidProcedureTable: return "The service provider returned an invalid or incomplete procedure table to the WSPStartup.";
		case WindowsSocketError::NoBuffers: return "No buffer space is available. The socket cannot be created.";
		case WindowsSocketError::NoProtocolSupport: return "The specified protocol is not supported.";
		case WindowsSocketError::Prototype: return "The specified protocol is the wrong type for this socket.";
		case WindowsSocketError::ProviderFailedInit: return "The service provider failed to initialize. This error is returned if a layered service provider (LSP) or namespace provider was improperly installed or the provider fails to operate correctly.";
		case WindowsSocketError::SocketTypeSupported: return "The specified socket type is not supported in this address family.";
		default: return "Unknown";
		}
	};
}