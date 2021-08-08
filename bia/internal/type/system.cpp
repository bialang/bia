#include "system.hpp"

#include "regex.hpp"
#include "string.hpp"
#include "void.hpp"

#include <limits>
#include <regex>
#include <string>

using namespace bia::internal::type;

System::System(util::Not_null<std::shared_ptr<memory::Allocator>> allocator)
    : _allocator{ allocator.get() }, _type_index{ allocator }
{}

System::System(System&& move) noexcept
    : _allocator{ move._allocator }, _type_index{ std::move(move._type_index) }
{
	std::swap(_id_counter, move._id_counter);
}

System::~System() noexcept
{
	for (const auto& i : _type_index) {
		_allocator->destroy(const_cast<type::Definition_base*>(i.first));
	}
}

System& System::operator=(System&& move) noexcept
{
	this->~System();
	new (this) System{ std::move(move) };
	return *this;
}
