#pragma once
#include "Ipv4.h"
#include "Ipv6.h"

namespace Net
{
	enum class IpVersion { Ipv4, Ipv6 };

	struct Ip
	{
		Ip(Ipv4 const & ip) noexcept;
		Ip(Ipv6 const & ip) noexcept;

		IpVersion GetVersion() const noexcept;
	private:
		friend std::string ToString(Ip const & ip) noexcept;
		std::string m_data;
		IpVersion m_version;
	};
	
	std::string ToString(Ip const & ip) noexcept;
}