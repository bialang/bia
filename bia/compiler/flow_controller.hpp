#ifndef BIA_COMPILER_FLOW_CONTROLLER_HPP_
#define BIA_COMPILER_FLOW_CONTROLLER_HPP_

#include "jumper.hpp"

#include <bia/resource/view.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/optional.hpp>
#include <vector>

namespace bia {
namespace compiler {

class Flow_controller
{
public:
	void start_flow(Jumper& jumper)
	{
		_jumpers.push_back({ &jumper, {} });
	}
	void start_flow(Jumper& jumper, const resource::View& label)
	{
		_jumpers.push_back({ &jumper, label });
	}
	void end_flow()
	{
		BIA_EXPECTS(!_jumpers.empty());
		_jumpers.pop_back();
	}
	bool break_flow()
	{
		return _control_flow(Jumper::Type::unconditional, Jumper::Destination::end);
	}
	bool break_flow(const resource::View& label)
	{
		return _control_flow(label, Jumper::Type::unconditional, Jumper::Destination::end);
	}
	bool continue_flow()
	{
		return _control_flow(Jumper::Type::unconditional, Jumper::Destination::start);
	}
	bool continue_flow(const resource::View& label)
	{
		return _control_flow(label, Jumper::Type::unconditional, Jumper::Destination::start);
	}

private:
	std::vector<std::pair<Jumper*, util::Optional<resource::View>>> _jumpers;

	bool _control_flow(Jumper::Type type, Jumper::Destination destination)
	{
		if (!_jumpers.empty()) {
			_jumpers.back().first->jump(type, destination);
		}
		return !_jumpers.empty();
	}
	bool _control_flow(const resource::View& label, Jumper::Type type, Jumper::Destination destination)
	{
		Jumper* jmp = nullptr;
		for (const auto& i : _jumpers) {
			if (i.second && i.second->compare(label) == 0) {
				jmp = i.first;
				break;
			}
		}
		if (!jmp) {
			return false;
		}
		jmp->jump(type, destination);
		return true;
	}
};

} // namespace compiler
} // namespace bia

#endif
