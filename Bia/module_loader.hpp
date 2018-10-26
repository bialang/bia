#pragma once

#include "config.hpp"
#include "module_library.hpp"
#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace modular
{

/**
 * @brief The module loader.
 *
 * @see @ref module_library
*/
class module_loader
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	 *
	 * @param [in] _allocator The memory allocator of the context.
	*/
	BIA_EXPORT module_loader(memory::allocator * _allocator) noexcept;
	module_loader(const module_loader & _copy) = delete;
	/**
	 * Move-Constructor.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	 *
	 * @param [in,out] _move The object that should be moved.
	*/
	module_loader(module_loader && _move) noexcept = default;
	/**
	 * Destructor.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	*/
	BIA_EXPORT ~module_loader() noexcept;
	/**
	 * Unloads a module.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	 *
	 * @param [in] _module The module. After this operation the module is invalid.
	 *
	 * @todo Implement function.
	*/
	BIA_EXPORT void unload_module(module_library * _module);
	/**
	 * Loads a BLL module.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	 *
	 * @param _filepath The directory where the module is located.
	 *
	 * @todo Add exceptions for errors.
	 *
	 * @return The loaded module if it succeeded.
	*/
	BIA_EXPORT module_library * load_bll(const char * _filepath, const char * _name);

private:
	/** The memory allocator of the context. */
	memory::allocator * _allocator;
};

}
}
}
