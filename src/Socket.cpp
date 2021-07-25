#include "Socket.h"
#include <iostream>

namespace Net
{
	Socket::Socket()
	{
		std::puts(__func__);
	}
	Socket::~Socket()
	{
		std::puts(__func__);
	}
}