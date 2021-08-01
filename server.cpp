#include "Ip.h"
#include "Socket.h"
#include "Log.h"

using namespace Net;

int main()
{
	Socket socket{ IpVersion::Ipv4, Type::TCP };

	Log( socket.Bind(Ipv4{ 127, 0, 0, 1 }, 8080) );

	Log( socket.Listen() );

	auto [accept_status, accepted_socket] = Log( socket.Accept() );

	auto [send_status, send_length] = Log( accepted_socket->Send("hello", 5) );

	char buffer[128];
	auto [recv_status, recv_length] = Log( accepted_socket->Receive(buffer, 128) );

	std::cout << "Received = '";
	std::cout.write(buffer, recv_length);
	std::cout << "'\n";
}