#include "Ip.h"
#include "Socket.h"
#include <iostream>

using namespace Net;

int main()
{
	Socket socket{ IpVersion::Ipv4, Type::TCP };
}