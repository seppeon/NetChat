#pragma once
#include <cstdint>
#include <string>

namespace Net
{
	struct Ipv6
	{
		uint16_t groups[8]{};
	};
	
	std::string ToString(Ipv6 const & ip) noexcept;
}