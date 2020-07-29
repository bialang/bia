#ifndef BIA_RESOURCE_SERIALIZER_HPP_
#define BIA_RESOURCE_SERIALIZER_HPP_

#include "view.hpp"

#include <cstdint>
#include <map>
#include <ostream>

namespace bia {
namespace resource {

class serializer
{
public:
	typedef std::uint16_t size_type;

	serializer(std::ostream& output) noexcept;

	void finish();
	size_type index_of(view view);
	void add_binding(size_type from, size_type to);

private:
	std::ostream& _output;
	std::ostream::pos_type _start;
	std::map<view, size_type> _map;
	size_type _index                     = 0;
	size_type _binding_count             = 0;
	std::ostream::pos_type _last_binding = std::ostream::off_type{ -1 };
};

} // namespace resource
} // namespace bia

#endif
