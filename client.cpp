#include "Ip.h"
#include "Socket.h"
#include <iostream>

using namespace Net;

int main()
{
	Socket socket{ IpVersion::IPV4, Type::TCP };
}