#pragma once

#include <utility>


namespace bia
{
namespace utility
{

template<typename _Ty, typename _Action>
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
	 * @throws See the constructor of @a _Ty.
	*/
	guard(_Ty && _object, _Action && _action) : _object(std::forward<_Ty>(_object)), _action(std::forward<_Action>(_action))
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
	 * @throws See the move constructor of @a _Ty.
	*/
	guard(guard<_Ty, _Action> && _move) : _object(std::move(_move._object)), _action(std::move(_move._action))
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
	 * @throws See @a _Action
	*/
	~guard()
	{
		if (is_valid()) {
			_action(_object);
		}
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
	_Ty & get() noexcept
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
	const _Ty & get() const noexcept
	{
		return _object;
	}

private:
	/** The state of this guard. */
	bool _valid;
	/** The guarded object. */
	_Ty _object;
	/** The action that is taken just before destruction of the guarded object. */
	_Action _action;
};

template<typename _Ty, typename _Action>
inline guard<_Ty, _Action> make_guard(_Ty && _object, _Action && _action)
{
	return guard<_Ty, _Action>(std::forward<_Ty>(_object), std::forward<_Action>(_action));
}

}
}