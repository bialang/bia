#pragma once

#include <utility>


namespace bia
{
namespace utility
{

template<typename Type, typename Action>
class guard
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.131.726
	 * @date 2-Jun-18
	 *
	 * @param _object The object that should be guarded.
	 * @param [in] _action The guard function.
	 *
	 * @throws See the constructor of @a Type.
	*/
	guard(Type&& _object, Action&& _action) : _object(std::forward<Type>(_object)), _action(std::forward<Action>(_action))
	{
		_valid = true;
	}
	/**
	 * Move-Constructor.
	 *
	 * @since 3.64.131.726
	 * @date 2-Jun-18
	 *
	 * @param [in] _move The guard that should be moved.
	 *
	 * @throws See the move constructor of @a Type.
	*/
	guard(guard<Type, Action>&& _move) : _object(std::move(_move._object)), _action(std::move(_move._action))
	{
		_valid = true;
		_move._valid = false;
	}
	/**
	 * Destructor.
	 *
	 * @since 3.64.131.726
	 * @date 2-Jun-18
	 *
	 * @throws See @a Action
	*/
	~guard()
	{
		if (is_valid()) {
			_action(_object);
		}
	}
	void invalidate() noexcept
	{
		_valid = false;
	}
	/**
	 * Checks if this guard is valid.
	 *
	 * @since 3.64.131.726
	 * @date 2-Jun-18
	 *
	 * @return true if this guard is valid, otherwise false.
	*/
	bool is_valid() const noexcept
	{
		return _valid;
	}
	/**
	 * Returns a reference to the guarded object.
	 *
	 * @since 3.64.131.726
	 * @date 2-Jun-18
	 *
	 * @return A reference.
	*/
	Type& get() noexcept
	{
		return _object;
	}
	/**
	 * Returns a reference to the guarded object.
	 *
	 * @since 3.64.131.726
	 * @date 2-Jun-18
	 *
	 * @return A reference.
	*/
	const Type& get() const noexcept
	{
		return _object;
	}

private:
	/** The state of this guard. */
	bool _valid;
	/** The guarded object. */
	Type _object;
	/** The action that is taken just before destruction of the guarded object. */
	Action _action;
};

template<typename Type, typename Action>
inline guard<Type, Action> make_guard(Type&& _object, Action&& _action)
{
	return guard<Type, Action>(std::forward<Type>(_object), std::forward<Action>(_action));
}

}
}