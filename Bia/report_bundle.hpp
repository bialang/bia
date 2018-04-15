#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>


namespace bia
{
namespace grammar
{

struct report;

typedef struct
{
	const report * begin;
	const report * end;
} report_range;

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
		TOKEN,
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
		struct
		{
			const char * string;
			size_t length;
		} token;
		report_range children;
	} content;
};

class report_bundle
{
public:
	/**
	 * Constructor.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	*/
	report_bundle() noexcept
	{
		_size = 0;
	}
	/**
	 * Adds a report to the bundle.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_report	Defines the report.
	*/
	inline void AddReport(report p_report)
	{
		if (_size < SIZE)
		{
			_report_array[_size++] = std::move(p_report);

			return;
		}
		else if (_size == SIZE)
			_report_vector.assign(_report_array, _report_array + _size++);

		_report_vector.push_back(std::move(p_report));
	}
	/**
	 * Clears the bundle completly.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	*/
	void clear() noexcept
	{
		_size = 0;
		_report_vector.clear();
	}
	/**
	 * Resets the bundle to a previous state.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_unOldState	Defines the previous state.
	*/
	inline void Reset(uint32_t p_unOldState)
	{
		if (_size > SIZE)
			_report_vector.erase(_report_vector.begin() + p_unOldState, _report_vector.end());
		else
			_size = p_unOldState;
	}
	/**
	 * Returns the current size of the bundle.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @return	The current size.
	*/
	uint32_t size() const noexcept
	{
		return _size > SIZE ? _report_vector.size() : _size;
	}
	/**
	 * Returns a pointer to the beginning.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @return	A pointer to the beginning.
	*/
	report * begin() noexcept
	{
		return _size > SIZE ? &*_report_vector.begin() : _report_array;
	}
	/**
	 * Returns a pointer to the end.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @return	A pointer to the end.
	*/
	report * end() noexcept
	{
		return _size > SIZE ? &*_report_vector.begin() : _report_array + _size;
	}

private:
	constexpr static uint32_t SIZE = 512;

	uint32_t _size;

	report _report_array[SIZE];

	std::vector<report> _report_vector;	/**	Stores the report when the array is full.	*/
};

class report_receiver
{
public:
	virtual ~report_receiver() = default;
	virtual void report(const report * _begin, const report * _end) = 0;
};

}
}