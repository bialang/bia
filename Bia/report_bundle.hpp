#pragma once

#include <cstdint>

#include "report.hpp"
#include "exception.hpp"


namespace bia
{
namespace grammar
{

/**
 * @brief A bunch of reports.
 *
 * A bundle of reports which define the structure of a Bia command.
 *
 * @see @ref report
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
	 * @throws exception::limitation_error If no more reports can be stored.
	*/
	void add(report _report)
	{
		// Limit reached
		if (_size >= _max_size) {
			throw exception::limitation_error(BIA_EM_REPORT_LIMIT);
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

/**
 * @brief A report receiver interface.
 *
 * An interface for receiving the interpreted reports to process them.
 *
 * @see @ref compiler::compiler
*/
class report_receiver
{
public:
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 8-Apr-18
	*/
	virtual ~report_receiver() noexcept = default;
	/**
	 * A function to report a range of reports.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _begin The beginnig of the report range.
	 * @param _end The ending of the report range.
	*/
	virtual void report(const report * _begin, const report * _end) = 0;
};

}
}