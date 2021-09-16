#include "object_builder.hpp"

#include "engine.hpp"

#include <bia/util/gsl.hpp>

using namespace bia;

Object_builder Object_builder_base::object(const std::string& name, bool immutable)
{
	return Object_builder{ _engine,
		                     Pointer{
		                       new internal::Typed_object{ _engine->context().global_namespace().type_system(),
		                                                   _engine->context().global_namespace().gc() } },
		                     name,
		                     false,
		                     immutable,
		                     _typed_object };
}

Object_builder_base::Object_builder_base(Engine* engine, Pointer typed_object) noexcept
    : _engine{ engine }, _typed_object{ std::move(typed_object) }
{}

Object_builder Object_builder_base::module(const std::string& name)
{
	BIA_EXPECTS(_typed_object.get() == &_engine->context().global_namespace());
	return Object_builder{ _engine,
		                     Pointer{
		                       new internal::Typed_object{ _engine->context().global_namespace().type_system(),
		                                                   _engine->context().global_namespace().gc() } },
		                     name,
		                     true,
		                     false,
		                     _typed_object };
}

void Object_builder::finish()
{
	BIA_EXPECTS(_typed_object != nullptr);
	if (_module) {
		static_cast<internal::Namespace*>(_parent.get())->put_import(_name, std::move(*_typed_object));
	} else {
		_parent->put_object(_name, std::move(*_typed_object), _immutable);
	}
	_typed_object = nullptr;
}

Object_builder::Object_builder(Engine* engine, Pointer typed_object, std::string name, bool module,
                               bool immutable, Pointer parent) noexcept
    : Object_builder_base{ engine, std::move(typed_object) }, _name{ std::move(name) }, _module{ module },
      _immutable{ immutable }, _parent{ std::move(parent) }
{}
