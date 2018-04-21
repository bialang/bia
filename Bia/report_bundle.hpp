#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

#include "member.hpp"
#include "operator.hpp"


namespace bia
{
namespace grammar
{

struct report
{
	typedef uint32_t custom_type;
	typedef uint32_t rule_type;
	typedef uint16_t token_type;

	constexpr static int custom_bits = 27;
	constexpr static int rule_bits = 22;
	constexpr static int token_bits = 32 - rule_bits;

	enum class TYPE : uint32_t
	{
		STRING,
		INT_VALUE,
		FLOAT_VALUE,
		DOUBLE_VALUE,
		MEMBER,
		OPERATOR_CODE,
		BEGIN,
		END,
		EMPTY_CHILD
	};

	TYPE type : 32 - custom_bits;
	uint32_t custom_parameter : custom_bits;
	uint32_t rule_id : rule_bits;
	uint32_t token_id : token_bits;
	union
	{
		const char * string;
		int64_t intValue;
		float floatValue;
		double doubleValue;
		const report *  end;
		framework::member * member;
		framework::OPERATOR operatorCode;
	} content;
};

/**
 * A bundle that holds reports which can be compiled.
*/
class report_bundle
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	*/
	report_bundle() noexcept
	{
		_size = 0;
	}
	/**
	 * Adds a report to the bundle.
	 *
	 * @since 2.39.82.486
	 * @date 16-Sep-17
	 *
	 * @param _report Defines the report.
	 *
	 * @throws	
	*/
	void add(report _report)
	{
		// Limit reached
		if (_size >= _max_size) {
			throw "";
		}

		_reports[_size++] = _report;
	}
	/**
	 * Clears the bundle completly.
	 *
	 * @since 2.39.82.486
	 * @date 16-Sep-17
	*/
	void reset() noexcept
	{
		_size = 0;
	}
	/**
	 * Rolls the bundle back to the old size.
	 *
	 * @since 2.39.82.486
	 * @date 16-Sep-17
	 *
	 * @param _old_size Defines the old size.
	*/
	void rollback(uint32_t _old_size) noexcept
	{
		_size = _old_size;
	}
	/**
	 * Returns the current size of the bundle.
	 *
	 * @since 2.39.82.486
	 * @date 16-Sep-17
	 *
	 * @return The current size.
	*/
	uint32_t size() const noexcept
	{
		return _size;
	}
	/**
	 * Returns a pointer to the beginning.
	 *
	 * @since 2.39.82.486
	 * @date 16-Sep-17
	 *
	 * @return A pointer to the beginning.
	*/
	report * begin() noexcept
	{
		return _reports;
	}
	/**
	 * Returns a pointer to the end.
	 *
	 * @since 2.39.82.486
	 * @date 16-Sep-17
	 *
	 * @return A pointer to the end.
	*/
	report * end() noexcept
	{
		return _reports + _size;
	}

private:
	constexpr static uint32_t _max_size = 512;

	/** Defines the amount of the currently held reports. */
	uint32_t _size;
	/** Hols all reports. */
	report _reports[_max_size];
};

class report_receiver
{
public:
	virtual ~report_receiver() = default;
	virtual void report(const report * _begin, const report * _end) = 0;
};

}
}