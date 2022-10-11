#include "Ipv4.h"

namespace Net
{
	static bool IsValid(Ipv4 const & ip) noexcept
	{
		for (auto v : ip.bytes)
		{
			if (v != 0) return true;
		}
		return false;
	}
	std::string ToString(Ipv4 const & ip) noexcept
	{
		if (not IsValid(ip)) return "";
		std::string output;
		for (auto v : ip.bytes)
		{
			output += std::to_string(v) + ".";
		}
		output.pop_back();
		return output;
	}
}