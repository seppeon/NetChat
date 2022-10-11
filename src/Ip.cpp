#include "Ip.h"

namespace Net
{
	Ip::Ip(Ipv4 const & ip) noexcept
		: m_data{ ToString(ip) }
		, m_version{ IpVersion::Ipv4 }
	{}

	Ip::Ip(Ipv6 const & ip) noexcept
		: m_data{ ToString(ip) }
		, m_version{ IpVersion::Ipv6 }
	{}

	IpVersion Ip::GetVersion() const noexcept
	{
		return m_version;
	}

	bool Ip::IsValid() const noexcept
	{
		return not m_data.empty();
	}

	std::string ToString(Ip const & ip) noexcept
	{
		return ip.m_data;
	}
}