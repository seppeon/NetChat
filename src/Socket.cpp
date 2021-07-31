#include "Socket.h"
#include "WinsockRaii.h"
#include "WindowsSocketRaii.h"

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

namespace Net
{
	std::string GetStatusDescription(BindStatus status) noexcept
	{
		switch(status)
		{
		case BindStatus::Success: return "Bind successful.";
		case BindStatus::NotInitialised: return "A successful Startup call must occur before using this function.";
		case BindStatus::NetworkDown: return "A network subsystem has failed.";
		case BindStatus::Access: return "This error is returned if nn attempt to bind a datagram socket to the broadcast address failed because the setsockopt option SO_BROADCAST is not enabled.";
		case BindStatus::AddressInUse: return "This error is returned if a process on the computer is already bound to the same fully qualified address and the socket has not been marked to allow address reuse with SO_REUSEADDR. For example, the IP ad";
		case BindStatus::AddressNotAvaliable: return "This error is returned if the specified address pointed to by the name parameter is not a valid local IP address on this computer.";
		case BindStatus::InvalidPointerArgument: return "This error is returned if the name parameter is NULL, the name or namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains an incorr";
		case BindStatus::OperationInProgress: return "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
		case BindStatus::SocketAlreadyBound: return "This error is returned of the socket s is already bound to an address.";
		case BindStatus::NoPortsAvaliable: return "An indication that there aren't enough ephemeral ports to allocate for the bind.";
		case BindStatus::NotASocket: return "This error is returned if the descriptor in the s parameter is not a socket.";
		}
		return "";
	}

	std::string GetStatusDescription(ListenStatus status) noexcept
	{
		switch(status)
		{
		case ListenStatus::Success: return "Listen successful.";
		case ListenStatus::NotInitialized: return "A successful WSAStartup call must occur before using this function.";
		case ListenStatus::NetworkDown: return "The network subsystem has failed.";
		case ListenStatus::AddressInUse: return "The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during execution";
		case ListenStatus::OperationInProgress: return "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
		case ListenStatus::UnboundSocket: return "The socket has not been bound with bind.";
		case ListenStatus::AlreadyConnected: return "The socket is already connected.";
		case ListenStatus::NoMoreDescriptors: return "No more socket descriptors are available.";
		case ListenStatus::NoBufferSpace: return "No buffer space is available.";
		case ListenStatus::NotASocket: return "This error is returned if the descriptor in the parameter is not a socket.";
		case ListenStatus::NotSupported: return "The referenced socket is not of a type that supports the listen operation. ";
		}
		return "";
	}
	
	std::string GetStatusDescription(AcceptStatus status) noexcept
	{
		switch (status)
		{
		case AcceptStatus::Success: return "Accepted successfully.";
		case AcceptStatus::NotInitialized: return "A successful WSAStartup call must occur before using this function.";
		case AcceptStatus::ConnectionReset: return "An incoming connection was indicated, but was subsequently terminated by the remote peer prior to accepting the call.";
		case AcceptStatus::Cancelled: return "A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall.";
		case AcceptStatus::ListenNotInvoked: return "The listen function was not invoked prior to accept.";
		case AcceptStatus::OperationInProgress: return "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
		case AcceptStatus::NoMoreDescriptors: return "The queue is nonempty upon entry to accept and there are no descriptors available.";
		case AcceptStatus::NetworkDown: return "The network subsystem has failed.";
		case AcceptStatus::NoBufferSpace: return "No buffer space is available.";
		case AcceptStatus::NotASocket: return "The descriptor is not a socket.";
		case AcceptStatus::NotSupported: return "The referenced socket is not a type that supports connection-oriented service.";
		case AcceptStatus::WouldBlock: return "The socket is marked as nonblocking and no connections are present to be accepted.";
		}
		return "";
	}

	std::string GetStatusDescription(SendStatus status) noexcept
	{
		switch (status)
		{
		case SendStatus::Success: return "Sent successfully.";
		case SendStatus::NotInitialized: return "A successful WSAStartup call must occur before using this function.";
		case SendStatus::NetworkDown: return "The network subsystem has failed.";
		case SendStatus::BroadcastAddressNotEnabled: return "The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt with the SO_BROADCAST socket option to enable use of the broadcast address.";
		case SendStatus::Cancelled: return "A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall.";
		case SendStatus::OperationInProgress: return "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
		case SendStatus::InvalidBufferParameter: return "The buf parameter is not completely contained in a valid part of the user address space.";
		case SendStatus::NetworkReset: return "The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress.";
		case SendStatus::NoBufferSpace: return "No buffer space is available.";
		case SendStatus::NotConnected: return "The socket is not connected.";
		case SendStatus::NotASocket: return "The descriptor is not a socket.";
		case SendStatus::NotSupported: return "MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations.";
		case SendStatus::Shutdown: return "The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH.";
		case SendStatus::WouldBlock: return "The socket is marked as nonblocking and the requested operation would block.";
		case SendStatus::MessageTooLarge: return "The socket is message oriented, and the message is larger than the maximum supported by the underlying transport.";
		case SendStatus::HostUnreachable: return "The remote host cannot be reached from this host at this time.";
		case SendStatus::UnboundSocket: return "The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled.";
		case SendStatus::ConnectionAborted: return "The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.";
		case SendStatus::ConnectionReset: return "The virtual circuit was reset by the remote side executing a hard or abortive close. For UDP sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a \"Port Unreachable\" ICMP packet. The application should close the socket as it is no longer usable.";
		case SendStatus::Timeout: return "The connection has been dropped, because of a network failure or because the system on the other end went down without notice. ";
		}
		return "";
	}

	std::string GetStatusDescription(ReceiveStatus status) noexcept
	{
		switch (status)
		{
		case ReceiveStatus::Success: return "Received successfully.";
		case ReceiveStatus::NotInitialized: return "A successful WSAStartup call must occur before using this function.";
		case ReceiveStatus::NetworkDown: return "The network subsystem has failed.";
		case ReceiveStatus::InvalidBufferParameter: return "The buf parameter is not completely contained in a valid part of the user address space.";
		case ReceiveStatus::NotConnected: return "The socket is not connected.";
		case ReceiveStatus::Cancelled: return "The (blocking) call was canceled through WSACancelBlockingCall.";
		case ReceiveStatus::OperationInProgress: return "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
		case ReceiveStatus::ConnectionReset: return "For a connection-oriented socket, this error indicates that the connection has been broken due to keep-alive activity that detected a failure while the operation was in progress. For a datagram socket, this error indicates that the time to live has expired.";
		case ReceiveStatus::NotASocket: return "The descriptor is not a socket.";
		case ReceiveStatus::NotSupported: return "MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations.";
		case ReceiveStatus::Shutdown: return "The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.";
		case ReceiveStatus::WouldBlock: return "The socket is marked as nonblocking and the receive operation would block.";
		case ReceiveStatus::MessageTooLarge: return "The message was too large to fit into the specified buffer and was truncated.";
		case ReceiveStatus::UnboundSocket: return "The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or negative.";
		case ReceiveStatus::ConnectionAborted: return "The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.";
		case ReceiveStatus::Timeout: return "The connection has been dropped because of a network failure or because the peer system failed to respond.";
		case ReceiveStatus::RemoteConnectionReset: return "The virtual circuit was reset by the remote side executing a hard or abortive close. The application should close the socket as it is no longer usable. On a UDP-datagram socket, this error would indicate that a previous send operation resulted in an ICMP \"Port Unreachable\" message.";
		}
		return "";
	}

	static auto GetFamily(IpVersion version) noexcept
	{
		switch (version)
		{
		case IpVersion::IPV4: return AF_INET;
		case IpVersion::IPV6: return AF_INET6;
		default: return 0;
		}
	}

	static sockaddr_in6 GetIpv6SocketStruct(Ip const & ip, uint16_t port) noexcept
 	{
		auto ip_version = ip.GetVersion();
		auto family = GetFamily(ip_version);
		sockaddr_in6 output
		{
			.sin6_family{ static_cast<short>(family) },
			.sin6_port{ htons(port) },
		};
		(void)inet_pton(family, ToString(ip).c_str(), (void *)&output.sin6_addr.s6_addr);
		return output;
	}

	static sockaddr_in GetIpv4SocketStruct(Ip const & ip, uint16_t port) noexcept
	{
		auto ip_version = ip.GetVersion();
		auto family = GetFamily(ip_version);
		sockaddr_in output
		{
			.sin_family{ static_cast<short>(family) },
			.sin_port{ htons(port) }
		};
		(void)inet_pton(family, ToString(ip).c_str(), (void *)&output.sin_addr);
		return output;
	}

	static sockaddr_in6 GetIpv6AnySocketStruct(uint16_t port) noexcept
 	{
		return
		{
			.sin6_family{ AF_INET6 },
			.sin6_port{ htons(port) },
			.sin6_addr{ in6addr_any }
		};
	}

	static sockaddr_in GetIpv4AnySocketStruct(uint16_t port) noexcept
	{
		return
		{
			.sin_family{ AF_INET },
			.sin_port{ htons(port) },
			.sin_addr{ INADDR_ANY }
		};
	}

	static BindStatus TranslateBindResult(int r) noexcept
	{
		if (r == SOCKET_ERROR)
		{
			switch (WSAGetLastError())
			{
			case WSANOTINITIALISED: return BindStatus::NotInitialised;
			case WSAENETDOWN: return BindStatus::NetworkDown;
			case WSAEACCES: return BindStatus::Access;
			case WSAEADDRINUSE: return BindStatus::AddressInUse;
			case WSAEADDRNOTAVAIL: return BindStatus::AddressNotAvaliable;
			case WSAEFAULT: return BindStatus::InvalidPointerArgument;
			case WSAEINPROGRESS: return BindStatus::OperationInProgress;
			case WSAEINVAL: return BindStatus::SocketAlreadyBound;
			case WSAENOBUFS: return BindStatus::NoPortsAvaliable;
			case WSAENOTSOCK: return BindStatus::NotASocket;
			}
		}
		return BindStatus::Success;
	}

	struct WindowsSocket : BaseSocket
	{
		WinsockRaii winsock;
		WindowsSocketRaii socket;

		WindowsSocket(socket_handle handle) noexcept
			: socket{ handle }
		{}

        WindowsSocket(int domain, int type, int protocol)
			: socket{ domain, type, protocol }
		{}

        WindowsSocket(WindowsSocket&&) noexcept = default;

        WindowsSocket& operator = (WindowsSocket&&) noexcept = default;

		virtual ~WindowsSocket() override {}

		BindStatus Bind(Ip const & ip, uint16_t port) const noexcept override
		{
			auto process = [&](auto sock_address) -> BindStatus
			{
				return TranslateBindResult(bind(socket.Get(), (sockaddr *)&sock_address, sizeof(sock_address)));
			};
			switch(ip.GetVersion())
			{
			case IpVersion::IPV4: return process(GetIpv4SocketStruct(ip, port));
			case IpVersion::IPV6: return process(GetIpv6SocketStruct(ip, port));
			default: 		      return BindStatus::Unknown;
			}
		}

		BindStatus Bind(IpVersion ip_version, uint16_t port) const noexcept override
		{
			auto process = [&](auto sock_address) -> BindStatus
			{
				return TranslateBindResult(bind(socket.Get(), (sockaddr *)&sock_address, sizeof(sock_address)));
			};
			switch(ip_version)
			{
			case IpVersion::IPV4: return process(GetIpv4AnySocketStruct(port));
			case IpVersion::IPV6: return process(GetIpv6AnySocketStruct(port));
			default: 		      return BindStatus::Unknown;
			}
		}

		ListenStatus Listen(size_t backlog) const noexcept override
		{
			auto r = listen(socket.Get(), backlog);
			if (r == SOCKET_ERROR)
			{
				switch (r)
				{
				case WSANOTINITIALISED: return ListenStatus::NotInitialized;
				case WSAENETDOWN: return ListenStatus::NetworkDown;
				case WSAEADDRINUSE: return ListenStatus::AddressInUse;
				case WSAEINPROGRESS: return ListenStatus::OperationInProgress;
				case WSAEINVAL: return ListenStatus::UnboundSocket;
				case WSAEISCONN: return ListenStatus::AlreadyConnected;
				case WSAEMFILE: return ListenStatus::NoMoreDescriptors;
				case WSAENOBUFS: return ListenStatus::NoBufferSpace;
				case WSAENOTSOCK: return ListenStatus::NotASocket;
				case WSAEOPNOTSUPP: return ListenStatus::NotSupported;
				default: return ListenStatus::Unknown;
				}
			}
			return ListenStatus::Success;
		}

		AcceptResult Accept() const noexcept override
		{
			auto r = accept(socket.Get(), NULL, NULL);
			if (r == INVALID_SOCKET)
			{
				switch(WSAGetLastError())
				{
				case WSANOTINITIALISED: return { AcceptStatus::NotInitialized };
				case WSAECONNRESET: 	return { AcceptStatus::ConnectionReset };
				case WSAEINTR: 			return { AcceptStatus::Cancelled };
				case WSAEINVAL: 		return { AcceptStatus::ListenNotInvoked };
				case WSAEINPROGRESS: 	return { AcceptStatus::OperationInProgress };
				case WSAEMFILE: 		return { AcceptStatus::NoMoreDescriptors };
				case WSAENETDOWN: 		return { AcceptStatus::NetworkDown };
				case WSAENOBUFS: 		return { AcceptStatus::NoBufferSpace };
				case WSAENOTSOCK: 		return { AcceptStatus::NotASocket };
				case WSAEOPNOTSUPP: 	return { AcceptStatus::NotSupported };
				case WSAEWOULDBLOCK: 	return { AcceptStatus::WouldBlock };
				default:				return { AcceptStatus::Unknown };
				}
			}
			WindowsSocket output{ r };
			return { .status = AcceptStatus::Success, .socket = std::make_unique<Socket>(std::move(static_cast<BaseSocket&>(output))) };
		}

		SendResult Send(const char * buf, size_t length, int flags) const noexcept override
		{
			auto r = send(socket.Get(), buf, static_cast<int>(length), flags); 
			if (r == SOCKET_ERROR)
			{
				switch( WSAGetLastError())
				{
				case WSANOTINITIALISED: return { SendStatus::NotInitialized };
				case WSAENETDOWN: return { SendStatus::NetworkDown };
				case WSAEACCES: return { SendStatus::BroadcastAddressNotEnabled };
				case WSAEINTR: return { SendStatus::Cancelled };
				case WSAEINPROGRESS: return { SendStatus::OperationInProgress };
				case WSAEFAULT: return { SendStatus::InvalidBufferParameter };
				case WSAENETRESET: return { SendStatus::NetworkReset };
				case WSAENOBUFS: return { SendStatus::NoBufferSpace };
				case WSAENOTCONN: return { SendStatus::NotConnected };
				case WSAENOTSOCK: return { SendStatus::NotASocket };
				case WSAEOPNOTSUPP: return { SendStatus::NotSupported };
				case WSAESHUTDOWN: return { SendStatus::Shutdown };
				case WSAEWOULDBLOCK: return { SendStatus::WouldBlock };
				case WSAEMSGSIZE: return { SendStatus::MessageTooLarge };
				case WSAEHOSTUNREACH: return { SendStatus::HostUnreachable };
				case WSAEINVAL: return { SendStatus::UnboundSocket };
				case WSAECONNABORTED: return { SendStatus::ConnectionAborted };
				case WSAECONNRESET: return { SendStatus::ConnectionReset };
				case WSAETIMEDOUT: return { SendStatus::Timeout };
				default: return { SendStatus::Unknown };
				}
			}
			return { SendStatus::Success, static_cast<size_t>(r) };
		}

		ReceiveResult Receive(char * buf, size_t length, int flags) const noexcept override
		{
			auto r = recv(socket.Get(), buf, static_cast<int>(length), flags);
			if (r == SOCKET_ERROR)
			{
				switch (WSAGetLastError())
				{
				case WSANOTINITIALISED: return { ReceiveStatus::NotInitialized };
				case WSAENETDOWN: return { ReceiveStatus::NetworkDown };
				case WSAEFAULT: return { ReceiveStatus::InvalidBufferParameter };
				case WSAENOTCONN: return { ReceiveStatus::NotConnected };
				case WSAEINTR: return { ReceiveStatus::Cancelled };
				case WSAEINPROGRESS: return { ReceiveStatus::OperationInProgress };
				case WSAENETRESET: return { ReceiveStatus::ConnectionReset };
				case WSAENOTSOCK: return { ReceiveStatus::NotASocket };
				case WSAEOPNOTSUPP: return { ReceiveStatus::NotSupported };
				case WSAESHUTDOWN: return { ReceiveStatus::Shutdown };
				case WSAEWOULDBLOCK: return { ReceiveStatus::WouldBlock };
				case WSAEMSGSIZE: return { ReceiveStatus::MessageTooLarge };
				case WSAEINVAL: return { ReceiveStatus::UnboundSocket };
				case WSAECONNABORTED: return { ReceiveStatus::ConnectionAborted };
				case WSAETIMEDOUT: return { ReceiveStatus::Timeout };
				case WSAECONNRESET: return { ReceiveStatus::RemoteConnectionReset };
				default: return { ReceiveStatus::Unknown };
				}
			}
			return { ReceiveStatus::Success, static_cast<size_t>(r) };
		}
	};

	static int GetDomain(IpVersion version) noexcept
	{
		switch (version)
		{
		case IpVersion::IPV4: return AF_INET;
		case IpVersion::IPV6: return AF_INET6;
		default: return 0;
		}
	}

	static int GetType(Type type) noexcept 
	{
		switch (type)
		{
		case Type::TCP: return SOCK_STREAM;
		case Type::UDP: return SOCK_DGRAM;
		default: return 0;
		}
	}

	static int GetProtocol(Type type) noexcept
	{
		switch (type)
		{
		case Type::TCP: return IPPROTO_TCP;
		case Type::UDP: return IPPROTO_UDP;
		default: return 0;
		}
	}

	Socket::Socket(IpVersion ip_version, Type type) noexcept
		: handle{ std::make_unique<WindowsSocket>(GetDomain(ip_version), GetType(type), GetProtocol(type)) }
	{}
	
	Socket::Socket(BaseSocket && socket) noexcept
		: handle{ std::make_unique<WindowsSocket>(static_cast<WindowsSocket&&>(socket)) }
	{}

	Socket::~Socket()
	{
	}

	BindStatus Socket::Bind(Ip const & ip, uint16_t port) const noexcept
	{
		return handle->Bind(ip, port);
	}

	BindStatus Socket::Bind(IpVersion ip_version, uint16_t port) const noexcept
	{
		return handle->Bind(ip_version, port);
	}

	ListenStatus Socket::Listen(size_t backlog) const noexcept
	{
		return handle->Listen(backlog);
	}

	AcceptResult Socket::Accept() const noexcept
	{
		return handle->Accept();
	}

	SendResult Socket::Send(const char * buf, size_t length, int flags) const noexcept
	{
		return handle->Send(buf, length, flags);
	}

	ReceiveResult Socket::Receive(char * buf, size_t length, int flags) const noexcept
	{
		return handle->Receive(buf, length, flags);
	}

	BaseSocket::~BaseSocket(){}
}