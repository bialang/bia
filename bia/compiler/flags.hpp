#ifndef BIA_COMPILER_FLAGS_HPP_
#define BIA_COMPILER_FLAGS_HPP_

namespace bia {
namespace compiler {

enum class flag
{

};

class flags
{
public:
	void enable(flag flag)
	{}
	void disable(flag flag)
	{}
	bool is_enabled(flag flag)
	{
		return true;
	}

private:
};

} // namespace compiler
} // namespace bia

#endif
