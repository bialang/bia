#ifndef BIA_RESOURCE_SERIALIZER_HPP_
#define BIA_RESOURCE_SERIALIZER_HPP_

#include "view.hpp"

#include <ostream>
#include <cstdint>
#include <map>

namespace bia {
namespace resource {

class serializer
{
public:
	typedef std::uint32_t size_type;

	serializer(std::ostream& output) noexcept;

	void finish();
	size_type index_of(view view);

private:
	std::ostream& _output;
	std::ostream::pos_type _start;
	size_type _index = 0;
	std::map<view, size_type> _map;
};

} // namespace resource
} // namespace bia

#endif