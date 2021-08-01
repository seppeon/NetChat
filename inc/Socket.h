#pragma once
#include "Ip.h"
#include <memory>
#include <limits>

namespace Net
{
	struct Socket;
	struct BaseSocket;

	enum class BindStatus
	{
		Success,
		Unknown,
		NotInitialised, 			// A successful WSAStartup call must occur before using this function.
		NetworkDown, 				// A network subsystem has failed.
		Access, 					// This error is returned if nn attempt to bind a datagram socket to the broadcast address failed because the setsockopt option SO_BROADCAST is not enabled.
		AddressInUse, 				// This error is returned if a process on the computer is already bound to the same fully qualified address and the socket has not been marked to allow address reuse with SO_REUSEADDR. For example, the IP address and port specified in the name parameter are already bound to another socket being used by another application. For more information, see the SO_REUSEADDR socket option in the SOL_SOCKET Socket Options reference, Using SO_REUSEADDR and SO_EXCLUSIVEADDRUSE, and SO_EXCLUSIVEADDRUSE.
		AddressNotAvaliable, 		// This error is returned if the specified address pointed to by the name parameter is not a valid local IP address on this computer.
		InvalidPointerArgument, 	// This error is returned if the name parameter is NULL, the name or namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains an incorrect address format for the associated address family, or the first two bytes of the memory block specified by name do not match the address family associated with the socket descriptor s.
		OperationInProgress, 		// A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
		SocketAlreadyBound, 		// This error is returned of the socket s is already bound to an address.
		NoPortsAvaliable, 			// An indication that there aren't enough ephemeral ports to allocate for the bind.
		NotASocket,					// This error is returned if the descriptor in the s parameter is not a socket.
	};
	std::string GetStatusDescription(BindStatus status) noexcept;

	enum class ListenStatus
	{
		Success,
		Unknown,
		NotInitialized, 			// A successful WSAStartup call must occur before using this function.
		NetworkDown,    			// The network subsystem has failed.
		AddressInUse,   			// The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during execution of the bind function, but could be delayed until this function if the bind was to a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be committed at the time of this function.
		OperationInProgress, 		// A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
		UnboundSocket, 				// The socket has not been bound with bind.
		AlreadyConnected,			// The socket is already connected.
		NoMoreDescriptors,			// No more socket descriptors are available.
		NoBufferSpace,				// No buffer space is available.
		NotASocket,					// This error is returned if the descriptor in the parameter is not a socket.
		NotSupported, 				// The referenced socket is not of a type that supports the listen operation. 
	};
	std::string GetStatusDescription(ListenStatus status) noexcept;

	enum class AcceptStatus
	{
		Success,
		Unknown,
		NotInitialized,				// A successful WSAStartup call must occur before using this function.
		ConnectionReset,			// An incoming connection was indicated, but was subsequently terminated by the remote peer prior to accepting the call.
		Cancelled,					// A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall.
		ListenNotInvoked,			// The listen function was not invoked prior to accept.
		OperationInProgress,		// A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
		NoMoreDescriptors,			// The queue is nonempty upon entry to accept and there are no descriptors available.
		NetworkDown,				// The network subsystem has failed.
		NoBufferSpace,				// No buffer space is available.
		NotASocket,					// The descriptor is not a socket.
		NotSupported,				// The referenced socket is not a type that supports connection-oriented service.
		WouldBlock,					// The socket is marked as nonblocking and no connections are present to be accepted.
	};
	std::string GetStatusDescription(AcceptStatus status) noexcept;

	enum class SendStatus
	{
		Success, 
		Unknown, 
		NotInitialized, 			// A successful WSAStartup call must occur before using this function.
		NetworkDown, 				// The network subsystem has failed.
		BroadcastAddressNotEnabled, // The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt with the SO_BROADCAST socket option to enable use of the broadcast address.
		Cancelled, 					// A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall.
		OperationInProgress, 		// A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
		InvalidBufferParameter, 	// The buf parameter is not completely contained in a valid part of the user address space.
		NetworkReset, 				// The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress.
		NoBufferSpace, 				// No buffer space is available.
		NotConnected, 				// The socket is not connected.
		NotASocket, 				// The descriptor is not a socket.
		NotSupported, 				// MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations.
		Shutdown, 					// The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH.
		WouldBlock, 				// The socket is marked as nonblocking and the requested operation would block.
		MessageTooLarge, 			// The socket is message oriented, and the message is larger than the maximum supported by the underlying transport.
		HostUnreachable, 			// The remote host cannot be reached from this host at this time.
		UnboundSocket, 				// The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled.
		ConnectionAborted, 			// The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.
		ConnectionReset, 			// The virtual circuit was reset by the remote side executing a hard or abortive close. For UDP sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a "Port Unreachable" ICMP packet. The application should close the socket as it is no longer usable.
		Timeout,					// The connection has been dropped, because of a network failure or because the system on the other end went down without notice. 
	};
	std::string GetStatusDescription(SendStatus status) noexcept;

	enum class ReceiveStatus
	{
		Success,
		Unknown,
		NotInitialized, 			// A successful WSAStartup call must occur before using this function.
		NetworkDown, 				// The network subsystem has failed.
		InvalidBufferParameter, 	// The buf parameter is not completely contained in a valid part of the user address space.
		NotConnected, 				// The socket is not connected.
		Cancelled, 					// The (blocking) call was canceled through WSACancelBlockingCall.
		OperationInProgress, 		// A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
		ConnectionReset, 			// For a connection-oriented socket, this error indicates that the connection has been broken due to keep-alive activity that detected a failure while the operation was in progress. For a datagram socket, this error indicates that the time to live has expired.
		NotASocket, 				// The descriptor is not a socket.
		NotSupported, 				// MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations.
		Shutdown, 					// The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.
		WouldBlock, 				// The socket is marked as nonblocking and the receive operation would block.
		MessageTooLarge, 			// The message was too large to fit into the specified buffer and was truncated.
		UnboundSocket, 				// The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or negative.
		ConnectionAborted, 			// The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.
		Timeout, 					// The connection has been dropped because of a network failure or because the peer system failed to respond.
		RemoteConnectionReset, 		// The virtual circuit was reset by the remote side executing a hard or abortive close. The application should close the socket as it is no longer usable. On a UDP-datagram socket, this error would indicate that a previous send operation resulted in an ICMP "Port Unreachable" message.
	};
	std::string GetStatusDescription(ReceiveStatus status) noexcept;

	enum class ConnectStatus
	{
		Success,
		Unknown,
		NotInitialized, 			// A successful WSAStartup call must occur before using this function.
		NetworkDown, 				// The network subsystem has failed.
		AddressInUse, 				// The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs when executing bind, but could be delayed until the connect function if the bind was to a wildcard address (INADDR_ANY or in6addr_any) for the local IP address. A specific address needs to be implicitly bound by the connect function.
		Cancelled, 					// The blocking Windows Socket 1.1 call was canceled through WSACancelBlockingCall.
		OperationInProgress, 		// A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
		ConnectInProgress, 			// A nonblocking connect call is in progress on the specified socket.
		InvalidAddress, 			// The remote address is not a valid address (such as INADDR_ANY or in6addr_any) .
		AddressFamilyNotSupported, 	// Addresses in the specified family cannot be used with this socket.
		ConnectionRefused, 			// The attempt to connect was forcefully rejected.
		InvalidSocketDetails, 		// The sockaddr structure pointed to by the name contains incorrect address format for the associated address family or the namelen parameter is too small. This error is also returned if the sockaddr structure pointed to by the name parameter with a length specified in the namelen parameter is not in a valid part of the user address space.
		ListeningSocket, 			// The parameter s is a listening socket, it shouldn't be.
		IsConnected, 				// The socket is already connected (connection-oriented sockets only).
		NetworkUnreachable, 		// The network cannot be reached from this host at this time.
		HostUnreachable, 			// A socket operation was attempted to an unreachable host.
		NoBufferSpace, 				// No buffer space is available. The socket cannot be connected.
		NotASocket, 				// The descriptor specified in the s parameter is not a socket.
		ConnectTimeout, 			// An attempt to connect timed out without establishing a connection.
		WouldBlock, 				// The socket is marked as nonblocking and the connection cannot be completed immediately.
		BroadcastNotEnabled, 		// An attempt to connect a datagram socket to broadcast address failed because setsockopt option SO_BROADCAST is not enabled. 
	};
	std::string GetStatusDescription(ConnectStatus status) noexcept;

	struct SendResult
	{
		SendStatus status;
		size_t length = 0;
	};

	struct ReceiveResult
	{
		ReceiveStatus status;
		size_t length = 0;
	};

	struct AcceptResult
	{
		AcceptStatus status;
		std::unique_ptr<Socket> socket;
	};

	enum class Type
	{
		TCP,
		UDP
	};

	struct Socket
	{
		Socket() = default;

		Socket(BaseSocket && socket) noexcept;

		Socket(IpVersion ip_version, Type type) noexcept;

		~Socket();

		BindStatus Bind(Ip const & ip, uint16_t port) const noexcept;

		ConnectStatus Connect(Ip const & ip, uint16_t port) const noexcept;

		BindStatus Bind(IpVersion ip_version, uint16_t port) const noexcept;

		ListenStatus Listen(size_t backlog = static_cast<size_t>(std::numeric_limits<int>::max())) const noexcept;

		AcceptResult Accept() const noexcept;

		SendResult Send(const char * buf, size_t length, int flags = 0) const noexcept;

		ReceiveResult Receive(char * buf, size_t length, int flags = 0) const noexcept;
	private:
		std::unique_ptr<BaseSocket> handle;
	};

	struct BaseSocket
	{
		virtual BindStatus Bind(Ip const & ip, uint16_t port) const noexcept = 0;

		virtual BindStatus Bind(IpVersion ip_version, uint16_t port) const noexcept = 0;

		virtual ListenStatus Listen(size_t backlog = static_cast<size_t>(std::numeric_limits<int>::max())) const noexcept = 0;

		virtual AcceptResult Accept() const noexcept = 0;

		virtual SendResult Send(const char * buf, size_t length, int flags = 0) const noexcept = 0;

		virtual ReceiveResult Receive(char * buf, size_t length, int flags = 0) const noexcept = 0;

		virtual ConnectStatus Connect(Ip const & ip, uint16_t port) const noexcept = 0;

		virtual ~BaseSocket();
	};
}