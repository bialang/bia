#include "../cbia.h"
#include "structs.hpp"

#include <bia/member/function/context.hpp>
#include <bia/thread/lock/guard.hpp>
#include <bia/thread/lock/mutex.hpp>

using namespace bia;
using namespace bia::cbia;

bia_signature_t bia_signature_new()
{
	return new Signature{};
}

int bia_signature_set_return(bia_signature_t signature, bia_definition_t definition)
{
	const auto sig = static_cast<Signature*>(signature);
	thread::lock::Guard<thread::lock::Mutex> _{ sig->mutex };
	// already in use
	if (sig->use_count) {
		return 1;
	}
	sig->signature.return_type = static_cast<const std::type_info*>(definition);
	return BIA_OK;
}

int bia_signature_set_argument(bia_signature_t signature, int index, bia_definition_t definition)
{
	const auto sig = static_cast<Signature*>(signature);
	thread::lock::Guard<thread::lock::Mutex> _{ sig->mutex };
	// already in use
	if (sig->use_count) {
		return 1;
	} else if (sig->signature.arguments.size() != index) {
		return 1;
	}
	sig->signature.arguments.push_back(static_cast<const std::type_info*>(definition));
	return BIA_OK;
}
