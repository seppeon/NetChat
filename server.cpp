#include "Ip.h"
#include "Socket.h"
#include <iostream>

using namespace Net;

int main()
{
	Socket socket{ IpVersion::Ipv4, Type::TCP };
	std::cout << GetStatusDescription(socket.Bind(Ipv4{ 127, 0, 0, 1 }, 8080)) << "\n";
	std::cout << GetStatusDescription(socket.Listen()) << "\n";

	auto [accept_status, accepted_socket] = socket.Accept();
	std::cout << GetStatusDescription(accept_status) << "\n";

	auto [send_status, send_length] = accepted_socket->Send("hello", 5);
	std::cout << GetStatusDescription(send_status) << "\n";

	char buffer[128];
	auto [recv_status, recv_length] = accepted_socket->Receive(buffer, 128);
	std::cout << GetStatusDescription(recv_status) << "\n";

	std::cout << "Received = '";
	std::cout.write(buffer, recv_length);
	std::cout << "'\n";
}