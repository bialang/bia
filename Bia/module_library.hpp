#pragma once

#include <cstdint>

#include "config.hpp"
#include "member.hpp"
#include "allocator.hpp"

#if defined(BIA_OS_WINDOWS)
#define BIA_MODULE_EXPORT __declspec(dllexport)
#else
#define BIA_MODULE_EXPORT
#endif

#define BIA_MODULE_LOAD_PREFIX "bia_module_load_"
#define BIA_MODULE_UNLOAD_PREFIX "bia_module_unload_"
#define BIA_REGISTER_MODULE_LIBRARY(_module_, _name_) extern "C" BIA_MODULE_EXPORT bia::machine::modular::module_library * bia_module_load_##_name_(bia::machine::memory::allocator * _allocator){ return _allocator->template construct<bia::machine::modular::module_library, _module_>(); } \
	extern "C" BIA_MODULE_EXPORT void bia_module_unload_##_name_(bia::machine::memory::allocator * _allocator, bia::machine::modular::module_library * _module) { _allocator->template destroy<_module_>({ static_cast<_module_*>(_module), sizeof(_module_) }); }


namespace bia
{
namespace machine
{

class machine_context;

namespace modular
{

/**
 * @brief A module interface.
 *
 * Every module implements this interface. This interface enables the loading of a module.
 *
 * @see @ref module_loader
*/
class module_library
{
public:
	/**
	 * Destructor.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	*/
	virtual ~module_library() = default;
	/**
	 * Loads the whole library.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	 *
	 * @param [in] _context The machine context of the script.
	 * @param [out] _destination The destination of the library.
	 *
	 * @return 0 if it succeeded, otherwise an error code.
	*/
	virtual int32_t load_all(bia::machine::machine_context * _context, bia::framework::member * _destination) = 0;
	/**
	 * Returns the version of the library.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	 *
	 * @return The version of the library.
	*/
	virtual int32_t version() noexcept = 0;
};

/** The module loader function signature. */
typedef module_library*(*module_loader_signature)(memory::allocator*);
/** The module unloader function signature. */
typedef void(*module_unloader_signature)(memory::allocator*, module_library*);

}
}
}
