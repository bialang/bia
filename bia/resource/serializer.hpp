#ifndef BIA_RESOURCE_SERIALIZER_HPP_
#define BIA_RESOURCE_SERIALIZER_HPP_

#include "view.hpp"

#include <cstdint>
#include <map>
#include <ostream>

namespace bia {
namespace resource {

class Serializer
{
public:
	typedef std::uint16_t Size;

	Serializer(std::ostream& output) noexcept;

	Size index_of(View view);

private:
	std::ostream& _output;
	std::map<View, Size> _map;
	Size _index                     = 0;
};

} // namespace resource
} // namespace bia

#endif
