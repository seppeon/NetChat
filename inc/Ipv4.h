#pragma once
#include <cstdint>
#include <string>

namespace Net
{
	struct Ipv4
	{
		uint8_t bytes[4]{};
	};

	std::string ToString(Ipv4 const & ip) noexcept;
}