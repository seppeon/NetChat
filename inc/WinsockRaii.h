#pragma once
#include <string>
#include <atomic>
#include <mutex>

namespace Net
{
	enum class WinsockErrors
	{
		SystemNotReady,			// The underlying network subsystem is not ready for network communication.
		VersionNotSupported,	// The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation.
		OperationInProgress,	// A blocking Windows Sockets 1.1 operation is in progress.
		TaskLimitReached,		// A limit on the number of tasks supported by the Windows Sockets implementation has been reached.
		InvalidParameter,		// The lpWSAData parameter is not a valid pointer.
		Unknown,
	};

	struct WinsockRaii
	{
		WinsockRaii();
		~WinsockRaii();

        WinsockRaii(WinsockRaii&&) noexcept = default;
        WinsockRaii& operator = (WinsockRaii&&) noexcept = default;

        WinsockRaii(WinsockRaii const&) = delete;
        WinsockRaii& operator = (WinsockRaii const&) = delete;

		WinsockErrors GetError() const noexcept;
	private:
		static std::mutex ref_lock;
		static int ref_count;
	};

	std::string GetErrorDescription(WinsockErrors error) noexcept;
}