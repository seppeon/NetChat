#include "Ip.h"
#include "Socket.h"
#include "Log.h"
#include <thread>

using namespace Net;

int main()
{
	auto start_server = [](uint16_t port)
	{
		try
		{
			Socket socket{IpVersion::Ipv4, Type::TCP};

			Log(socket.Bind(IpVersion::Ipv4, port));
			Log(socket.Listen());

			auto [accept_status, accepted_socket] = Log(socket.Accept());

			auto [send_status, send_length] = Log(accepted_socket->Send("hello", 5));

			char buffer[128];
			auto [recv_status, recv_length] = Log(accepted_socket->Receive(buffer, 128));

			std::cout << "Received = '";
			std::cout.write(buffer, recv_length);
			std::cout << "'\n";
		}
		catch (std::logic_error & error)
		{
			std::cout << error.what();
		}
	};

	std::thread server1{start_server, 8080};
	std::thread server2{start_server, 8081};

	server1.join();
	server2.join();
}