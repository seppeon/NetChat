#include "Ipv6.h"
#include <sstream>
#include <iostream>

namespace Net
{
	template< typename T >
	std::string IntToHex( T const & i ) noexcept
	{
		std::stringstream stream;
		stream << std::hex << i;
		return stream.str();
	}

	static bool IsValid(Ipv6 const & ip) noexcept
	{
		for (auto v : ip.groups)
		{
			if (v != 0) return true;
		}
		return false;
	}

	std::string ToString(Ipv6 const & ip) noexcept
	{
		if (not IsValid(ip)) return "";
		std::string output;
		for (auto v : ip.groups)
		{
			output += IntToHex(v) + ":";
		}
		output.pop_back();
		return output;
	}
}