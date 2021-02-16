#ifndef BIA_TOKENIZER_READER_HPP_
#define BIA_TOKENIZER_READER_HPP_

#include "location.hpp"

#include <bia/string/encoding/encoder.hpp>
#include <istream>

namespace bia {
namespace tokenizer {

class Reader
{
public:
	struct Backup
	{
		std::istream::pos_type position;
		Location location;
	};

	Reader(std::istream& input, string::encoding::Encoder& encoder) noexcept
	    : _input{ input }, _encoder{ encoder }
	{
		_location.line      = 1;
		_location.character = 1;
	}
	void restore(const Backup& backup)
	{
		// TODO check input
		_input.seekg(backup.position);
		_location = backup.location;
	}
	bool eof()
	{
		_input.peek();
		return _input.eof();
	}
	Backup backup() const noexcept
	{
		return { _input.tellg(), _location };
	}
	string::encoding::code_point_type read()
	{
		const auto pos = _input.tellg();
		const auto cp  = _encoder.read(_input);
		// update location
		if (cp == '\n') {
			_location.line++;
			_location.character = 0;
		}
		if (cp != string::encoding::Encoder::eof) {
			_location.character++;
			_location.offset += _input.tellg() - pos;
			_location.character_offset++;
		}
		return cp;
	}
	Location location() const noexcept
	{
		return _location;
	}

private:
	std::istream& _input;
	string::encoding::Encoder& _encoder;
	Location _location{};
};

} // namespace tokenizer
} // namespace bia

#endif
