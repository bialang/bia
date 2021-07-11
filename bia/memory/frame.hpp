#ifndef BIA_MEMORY_FRAME_HPP_
#define BIA_MEMORY_FRAME_HPP_

#include <bia/internal/type/framer.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/util/algorithm.hpp>
#include <bia/util/type_traits/is_frameable.hpp>
#include <bia/util/type_traits/type_at.hpp>
#include <bia/util/type_traits/type_select.hpp>
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
	Frame(util::Span<util::Byte*> space, std::size_t offset) noexcept : _space{ space }, _offset{ offset }
	{}
	Frame(const Frame& parent, std::size_t offset) noexcept
	    : _space{ parent._space }, _offset{ offset }
	{}
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

		const auto position = _space.begin() + offset + _offset;
		if (reinterpret_cast<std::intptr_t>(position) % Framer::alignment()) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _space.begin() || position + Framer::size() > _space.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		return Framer::unframe({ position, Framer::size() });
	}
	template<std::size_t Index, typename... Parameters>
	typename util::type_traits::type_at<Index, Parameters...>::type load_parameter()
	{
		static_assert(util::sum(static_cast<int>(util::type_traits::Is_frameable<Parameters>::value)...) ==
		                sizeof...(Parameters),
		              "all parameters must be frameable");
		// TODO
		return _load_parameter<typename util::type_traits::type_at<Index, Parameters...>::type>(
		  util::type_traits::type_select<0, Index + 1, gc::GC_able<void*>, Parameters...>::value);
	}

protected:
	util::Span<util::Byte*> _space;
	std::size_t _offset;

	template<typename Parameter, typename... PreviousParameters>
	Parameter _load_parameter(util::type_traits::type_container<PreviousParameters...>)
	{
		return load<Parameter>(util::sum(
		  util::aligned(internal::type::Framer<PreviousParameters>::size(), alignof(std::max_align_t))...));
	}
};

template<>
class Frame<true> : public Frame<false>
{
public:
	Frame(util::Span<util::Byte*> space, gc::GC& gc, std::size_t offset) noexcept
	    : Frame<false>{ space, offset }, _gc{ gc }
	{}
	Frame(Frame& parent, std::size_t offset) noexcept : Frame<false>{ parent, offset }, _gc{ parent._gc }
	{}
	template<typename Type>
	void store(std::int32_t offset, const Type& value)
	{
		static_assert(util::type_traits::Is_frameable<Type>::value, "Type is not frameable");
		using Framer = internal::type::Framer<Type>;

		const auto position = _space.begin() + offset + _offset;
		if (reinterpret_cast<std::intptr_t>(position) % Framer::alignment()) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _space.begin() || position + Framer::size() > _space.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		Framer::frame(_gc, { position, Framer::size() }, value);
	}

private:
	gc::GC& _gc;
};

} // namespace memory
} // namespace bia

#endif
