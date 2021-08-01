#pragma once
#include <iostream>

namespace Net
{
	template <typename T>
	concept Describable = requires(T status){ GetStatusDescription(status); };

	template <typename T>
	concept NestedDescribable = requires(T status){ GetStatusDescription(status.status); };

	template <Describable T>
	auto Log(T && status)
	{
		std::cout << GetStatusDescription(status) << "\n";
		return status;
	}

	template <NestedDescribable T>
	auto Log(T && status)
	{
		std::cout << GetStatusDescription(status.status) << "\n";
		return std::move(status);
	}
}