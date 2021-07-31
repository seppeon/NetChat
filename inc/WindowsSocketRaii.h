#pragma once
#include <string>

namespace Net
{
	enum class WindowsSocketError
	{
		WinsockNotInitialized,			// A successful WSAStartup call must occur before using this function.
		NetworkSystemDown,				// The network subsystem or the associated service provider has failed.
		AddressFamilyNotSupported,		// The specified address family is not supported. For example, an application tried to create a socket for the AF_IRDA address family but an infrared adapter and device driver is not installed on the local computer.
		OperationInProgress,			// A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
		NoMoreDescriptorsAvaliable,		// No more socket descriptors are available.
		InvalidArgument,				// An invalid argument was supplied. This error is returned if the af parameter is set to AF_UNSPEC and the type and protocol parameter are unspecified.
		InvalidProvider,				// The service provider returned a version other than 2.2.
		InvalidProcedureTable,			// The service provider returned an invalid or incomplete procedure table to the WSPStartup.
		NoBuffers,						// No buffer space is available. The socket cannot be created.
		NoProtocolSupport,				// The specified protocol is not supported.
		Prototype,						// The specified protocol is the wrong type for this socket.
		ProviderFailedInit,				// The service provider failed to initialize. This error is returned if a layered service provider (LSP) or namespace provider was improperly installed or the provider fails to operate correctly.
		SocketTypeSupported,			// The specified socket type is not supported in this address family. 
		Unknown,						// Unknown
	};

	using socket_handle = unsigned long long;

	struct WindowsSocketRaii
	{
		inline WindowsSocketRaii(socket_handle handle) noexcept 
			: m_socket{ handle }
		{}
        WindowsSocketRaii(int domain, int type, int protocol);
		~WindowsSocketRaii();

		unsigned long long Get() const noexcept;

		WindowsSocketError GetError() const noexcept;

        WindowsSocketRaii(WindowsSocketRaii&&) noexcept;
        WindowsSocketRaii& operator = (WindowsSocketRaii&&) noexcept;

        WindowsSocketRaii(WindowsSocketRaii const&) = delete;
        WindowsSocketRaii& operator = (WindowsSocketRaii const&) = delete;
	private:
		socket_handle m_socket;
	};

	std::string GetErrorDescription(WindowsSocketError error) noexcept;
}