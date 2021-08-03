#ifndef BIA_INTERNAL_STRING_KEY_HPP_
#define BIA_INTERNAL_STRING_KEY_HPP_

#include <bia/resource/view.hpp>
#include <bia/util/algorithm.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <ostream>
#include <string>

namespace bia {
namespace internal {

typedef util::Variant<std::string, util::Span<const char*>, resource::View> String_key;

inline int compare(const String_key& left, const String_key& right)
{
	BIA_EXPECTS(!left.empty() && !right.empty());
	if (left.is_type<std::string>()) {
		const auto& lhs = left.get<std::string>();
		if (right.is_type<std::string>()) {
			const auto& rhs = right.get<std::string>();
			return util::compare_ranges(lhs.c_str(), lhs.c_str() + lhs.length(), rhs.c_str(),
			                            rhs.c_str() + rhs.length());
		} else if (right.is_type<util::Span<const char*>>()) {
			const auto& rhs = right.get<util::Span<const char*>>();
			return util::compare_ranges(lhs.c_str(), lhs.c_str() + lhs.length() + 1, rhs.begin(), rhs.end());
		}
		return right.get<resource::View>().compare(lhs.c_str(), lhs.length() + 1) * -1;
	} else if (left.is_type<util::Span<const char*>>()) {
		const auto& lhs = left.get<util::Span<const char*>>();
		if (right.is_type<std::string>()) {
			const auto& rhs = right.get<std::string>();
			return util::compare_ranges(lhs.begin(), lhs.end(), rhs.c_str(), rhs.c_str() + rhs.length() + 1);
		} else if (right.is_type<util::Span<const char*>>()) {
			const auto& rhs = right.get<util::Span<const char*>>();
			return util::compare_ranges(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		return right.get<resource::View>().compare(lhs.data(), lhs.size()) * -1;
	}
	const auto& lhs = left.get<resource::View>();
	if (right.is_type<std::string>()) {
		const auto& rhs = right.get<std::string>();
		return lhs.compare(rhs.c_str(), rhs.length() + 1);
	} else if (right.is_type<util::Span<const char*>>()) {
		const auto& rhs = right.get<util::Span<const char*>>();
		return lhs.compare(rhs.data(), rhs.size());
	}
	return lhs.compare(right.get<resource::View>());
}

struct String_comparator
{
	bool operator()(const String_key& left, const String_key& right) const
	{
		return compare(left, right) < 0;
	}
};

inline std::ostream& operator<<(std::ostream& output, const String_key& key)
{
	if (key.is_type<std::string>()) {
		output << key.get<std::string>();
	} else if (key.is_type<util::Span<const char*>>()) {
		const auto span = key.get<util::Span<const char*>>();
		output.write(span.data(), span.size() - 1);
	} else if (key.is_type<resource::View>()) {
		for (const auto byte : key.get<resource::View>()) {
			output.put(static_cast<char>(byte));
		}
	} else {
		output << "(null)";
	}
	return output;
}

} // namespace internal
} // namespace bia

#endif
