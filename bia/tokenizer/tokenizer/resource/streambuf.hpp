#ifndef BIA_TOKENIZER_RESOURCE_STREAMBUF_HPP_
#define BIA_TOKENIZER_RESOURCE_STREAMBUF_HPP_

#include <gc/memory/space.hpp>
#include <streambuf>
#include <util/gsl.hpp>

namespace bia {
namespace tokenizer {
namespace resource {

class manager;

/**
 * An output stream buffer for the @ref manager.
 *
 * @see @ref manager
 */
class streambuf : public std::streambuf
{
public:
	streambuf(const streambuf& copy) = delete;
	streambuf(streambuf&& move) noexcept;
	~streambuf();
	void close() noexcept;
	/**
	 * Checks whether this streambuf is valid.
	 *
	 * @returns `true` if valid, otherwise `false`
	 */
	bool valid() const noexcept;

protected:
	int_type sync() override;
	int_type overflow(int_type ch = traits_type::eof()) override;

private:
	friend manager;

	/** if non-null the parent */
	manager* _manager  = nullptr;
	std::size_t _begin = 0;

	/**
	 * Constructor.
	 *
	 * @param space the destination of the data
	 */
	streambuf(util::not_null<manager*> manager);
};

} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif