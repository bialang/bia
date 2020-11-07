#ifndef BIA_TOOL_ERROR_HPP_
#define BIA_TOOL_ERROR_HPP_

#include <system_error>
#include <type_traits>

enum class errc
{
	success,

	file_not_found
};

inline const std::error_category& bia_tool_category() noexcept
{
	static class : public std::error_category
	{
	public:
		const char* name() const noexcept override
		{
			return "bia-tool";
		}
		std::string message(int ec) const override
		{
			switch (static_cast<errc>(ec)) {
			case errc::success: return "(success)";
			case errc::file_not_found: return "file not found";
			default: return "(unknown error)";
			}
		}
	} category;
	return category;
}

inline std::error_code make_error_code(errc ec) noexcept
{
	return { static_cast<int>(ec), bia_tool_category() };
}

namespace std {
template<>
struct is_error_code_enum<::errc> : true_type
{};
} // namespace std

#endif
