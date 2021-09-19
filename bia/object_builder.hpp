#ifndef BIA_OBJECT_BUILDER_HPP_
#define BIA_OBJECT_BUILDER_HPP_

#include <bia/internal/typed_object.hpp>
#include <bia/util/gsl.hpp>
#include <memory>
#include <string>
#include <utility>

namespace bia {

class Engine;
class Object_builder;

class Object_builder_base
{
public:
	/**
	 * Sets the globally available symbol to the given function.
	 *
	 * @tparam Invokable The function type.
	 * @param name The global name.
	 * @param invokable The invokable function.
	 * @param immutable If `true`, the Bia code is not allowed to overwrite the symbol value.
	 */
	template<typename Invokable>
	void function(const std::string& name, Invokable&& invokable, bool immutable = true)
	{
		_typed_object->put_invokable(name, std::forward<Invokable>(invokable), immutable);
	}
	void function(const std::string& name, member::function::Dynamic_invokable invokable,
	              member::function::Signature signature, bool immutable = true)
	{
		_typed_object->put_invokable(name, std::move(invokable), std::move(signature), immutable);
	}
	template<typename Type>
	void variable(const std::string& name, Type&& value, bool immutable = true)
	{
		_typed_object->put_value(name, std::forward<Type>(value), immutable);
	}
	Object_builder object(const std::string& name, bool immutable = true);

protected:
	friend Engine;
	typedef std::shared_ptr<internal::Typed_object> Pointer;

	Engine* _engine;
	Pointer _typed_object;

	Object_builder_base(Engine* engine, Pointer typed_object) noexcept;
	Object_builder module(const std::string& name);
};

class Object_builder : public Object_builder_base
{
public:
	void finish();

private:
	friend Object_builder_base;

	std::string _name;
	bool _module;
	bool _immutable;
	Pointer _parent;

	Object_builder(Engine* engine, Pointer typed_object, std::string name, bool module, bool immutable,
	               Pointer parent) noexcept;
};

} // namespace bia

#endif
