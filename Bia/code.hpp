#pragma once


namespace bia
{
namespace machine
{

class code
{
public:
	virtual ~code() noexcept = default;
	virtual void execute() = 0;
	virtual void clear() = 0;
	virtual bool is_executable() const = 0;
};

}
}