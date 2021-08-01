#include "Ip.h"
#include "Socket.h"
#include "Log.h"

using namespace Net;

int main()
{
	Socket socket{IpVersion::Ipv4, Type::TCP};
	Log(socket.Connect(Ipv4{127, 0, 0, 1}, 8080));

	std::string line;
	while (std::getline(std::cin, line))
	{
		Log(socket.Send(line.data(), line.size()));
	}
}