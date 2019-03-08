#pragma once

#include <map>
#include <vector>

#include "name_manager.hpp"


namespace bia
{
namespace utility
{

/**
 * @brief Holds entry names and their indices.
*/
class index_map
{
public:
	/**
	 * Returns the index of the entry. If it does not exist, a new entry will be created.
	 *
	 * @since 3.72.149.810
	 * @date 18-Jan-19
	 *
	 * @param _name The name of the entry.
	 *
	 * @throws See std::map::find() and std::map::insert().
	 *
	 * @return The index of the entry.
	*/
	size_t get_or_insert(machine::name_manager::name_t _name)
	{
		auto _result = _index.find(_name);

		if (_result != _index.end()) {
			return _result->second;
		}

		auto _tmp = _index.size();

		_index.insert({ _name, _tmp });

		return _tmp;
	}
	/**
	 * Creates a entry list from all known entries.
	 *
	 * @since 3.72.149.810
	 * @date 18-Jan-19
	 *
	 * @tparam Type The resulting type in the list.
	 * @tparam Converter The converter function type.
	 *
	 * @param [in] _converter The converter function.
	 *
	 * @throws See @a Converter.
	 * @throws See std::vector::resize().
	 *
	 * @return A list of the converted entries.
	*/
	template<typename Type, typename Converter>
	std::vector<Type> to_list(Converter && _converter) const
	{
		std::vector<Type> _list;

		_list.resize(_index.size());

		for (auto & _index : _index) {
			_list[_index.second] = _converter(_index.first);
		}

		return _list;
	}

private:
	/** Holds all entries and their indices. */
	std::map<machine::name_manager::name_t, size_t> _index;
};

}
}