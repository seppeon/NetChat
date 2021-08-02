#include "Ip.h"
#include "Socket.h"
#include "Log.h"

using namespace Net;

int main()
{
	Socket socket{IpVersion::Ipv4, Type::TCP};
	Log(socket.Connect(Ipv4{127, 0, 0, 1}, 8080));

	// PROBLEM 0:
	//	Add support for setsockopt and getsockopt, research why they are useful.

	// PROBLEM 1:
	// 	How do we allow this to send and receive at the same time?

	// PROBLEM 2:
	// 	How do we allow this to do things and receive things at the same time?

	std::string line;
	while (std::getline(std::cin, line))
	{
		Log(socket.Send(line.data(), line.size()));
	}
}