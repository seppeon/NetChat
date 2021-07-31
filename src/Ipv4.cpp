#include "Ipv4.h"

namespace Net
{
	std::string ToString(Ipv4 const & ip) noexcept
	{
		std::string output;
		for (auto v : ip.bytes)
		{
			output += std::to_string(v) + ".";
		}
		output.pop_back();
		return output;
	}
}