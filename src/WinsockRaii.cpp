#include "WinsockRaii.h"
#include <mutex>

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <ws2tcpip.h> 
#pragma comment(lib, "ws2_32.lib")

namespace Net
{
	static constexpr auto winsock_version = MAKEWORD(2,2);
	int WinsockRaii::ref_count = 0;
	std::mutex WinsockRaii::ref_lock{};

	WinsockRaii::WinsockRaii()
	{
		std::scoped_lock lock{ ref_lock };
		if (ref_count++ == 0)
		{
			WSADATA wsa;
			if ( WSAStartup(winsock_version, &wsa) != 0)
				throw GetError();
		}
	}

	WinsockRaii::~WinsockRaii()
	{
		std::scoped_lock lock{ ref_lock };
		if (--ref_count == 0)
		{
			WSACleanup();
		}
	}

	WinsockErrors WinsockRaii::GetError() const noexcept
	{
		switch (WSAGetLastError())
		{
		case WSASYSNOTREADY: 	 return WinsockErrors::SystemNotReady;
		case WSAVERNOTSUPPORTED: return WinsockErrors::VersionNotSupported;
		case WSAEINPROGRESS: 	 return WinsockErrors::OperationInProgress;
		case WSAEPROCLIM: 		 return WinsockErrors::TaskLimitReached;
		case WSAEFAULT: 		 return WinsockErrors::InvalidParameter;
		default:				 return WinsockErrors::Unknown;
		}
	}

	std::string GetErrorDescription(WinsockErrors error) noexcept
	{
		switch (error)
		{
		case WinsockErrors::SystemNotReady: return "The underlying network subsystem is not ready for network communication.";
		case WinsockErrors::VersionNotSupported: return "The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation.";
		case WinsockErrors::OperationInProgress: return "A blocking Windows Sockets 1.1 operation is in progress.";
		case WinsockErrors::TaskLimitReached: return "A limit on the number of tasks supported by the Windows Sockets implementation has been reached.";
		case WinsockErrors::InvalidParameter: return "The lpWSAData parameter is not a valid pointer.";
		default: return "Unknown";
		}
	}
}