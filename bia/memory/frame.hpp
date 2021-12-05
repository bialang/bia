#ifndef BIA_MEMORY_FRAME_HPP_
#define BIA_MEMORY_FRAME_HPP_

#include <bia/internal/type/framer.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/util/algorithm.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/type_traits/is_frameable.hpp>
#include <cstdint>

namespace bia {
namespace memory {

/**
 * A frame operates on the given memory and stores or loads data from it. It requires the GC to frame the
 * given objects correctly.
 *
 * @tparam Writeable Whether write actions are allowed.
 */
template<bool Writable>
class Frame;

template<>
class Frame<false>
{
public:
	Frame() noexcept = default;
	Frame(util::Span<util::Byte*> space) noexcept : _space{ space }
	{
		// BIA_EXPECTS(util::is_aligned(_space.begin(), alignof(std::max_align_t)));
	}
	Frame(const Frame& parent, std::size_t offset) : _space{ parent._space.subspan(offset) }
	{
		// BIA_EXPECTS(util::is_aligned(_space.begin(), alignof(std::max_align_t)));
	}
	/**
	 * Loads a frameable type.
	 *
	 * @exception error::Exception
	 *     - `error::Code::bad_stack_alignment` If the new position alignment is invalid.
	 *     - `error::Code::out_of_stack` If the stack is full.
	 * @tparam Type A framable type that must satisfy the requirements of util::type_traits::Is_frameable.
	 * @param offset The offset of the location relative to the current frame beginning.
	 * @returns The loaded type.
	 */
	template<typename Type>
	Type load(std::int32_t offset) const
	{
		static_assert(util::type_traits::Is_frameable<Type>::value, "Type is not frameable");
		using Framer = internal::type::Framer<Type>;

		const auto position = _space.begin() + offset;
		if (reinterpret_cast<std::intptr_t>(position) % Framer::alignment()) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _space.begin() || position + Framer::size() > _space.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		return Framer::unframe({ position, Framer::size() });
	}
	util::Span<util::Byte*> underlying_memory() noexcept
	{
		return _space;
	}

protected:
	util::Span<util::Byte*> _space;
};

template<>
class Frame<true> : public Frame<false>
{
public:
	Frame() noexcept = default;
	Frame(util::Span<util::Byte*> space, gc::GC* gc) noexcept : Frame<false>{ space }, _gc{ gc }
	{}
	Frame(Frame& parent, std::size_t offset) : Frame<false>{ parent, offset }, _gc{ parent._gc }
	{}
	Frame(const Frame& copy) noexcept = default;
	~Frame() noexcept                 = default;
	template<typename Type>
	std::size_t store(std::int32_t offset, const Type& value)
	{
		static_assert(util::type_traits::Is_frameable<Type>::value, "Type is not frameable");
		using Framer = internal::type::Framer<Type>;

		const auto position = _space.begin() + offset;
		if (reinterpret_cast<std::intptr_t>(position) % Framer::alignment()) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _space.begin() || position + Framer::size() > _space.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		Framer::frame(_gc, { position, Framer::size() }, value);
		return Framer::size();
	}
	gc::GC* gc() noexcept
	{
		return _gc;
	}
	Frame& operator=(const Frame& copy) noexcept = default;

private:
	gc::GC* _gc = nullptr;
};

} // namespace memory
} // namespace bia

#endif
