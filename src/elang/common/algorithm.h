/*****************************************************************//**
 * @file   algorithm.h
 * @brief  A couple or more simple algorithms that is not so readily available in standard libraries
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_ALGORITHM_H
#define  EL_ALGORITHM_H
#include <algorithm>
#include "type_traits.h"

namespace el 
{
	/**
	 * @brief Min function.
	 *
	 * Returns the minimum value of @p left or @p right.
	 *
	 * @param left Value.
	 * @param right Other value.
	 * @return Smaller value of the two.
	 */
	template<typename T, typename U>
	constexpr typename std::common_type_t<T, U> const& min(const T& left, const U& right) {
		return (left < right) ? left : right;
	}

	/**
	 * @brief Max function
	 *
	 * Returns the maximum value of @p left or @p right.
	 *
	 * @param left Value.
	 * @param right Other value.
	 * @return Larger value of the two.
	 */
	template<typename T, typename U>
	constexpr typename std::common_type_t<T, U> const& max(const T& left, const U& right) {
		return (left > right) ? left : right;
	}

	/**
	 * Clamp function
	 *
	 * Returns a value that is clamped by the bounds of @p left or @p right.
	 * If param @p val is larger than l and smaller than r, then return the same value as @p val.
	 *
	 * @param val Value in question.
	 * @param low Low limit.
	 * @param high High limit.
	 * @return The new clamped value.
	 */
	template<typename T>
	constexpr T const& clamp(const T& val, const identity_t<T>& low, const identity_t<T>& high) {
		return (val < low) ? low : (val > high) ? high : val;
	}
}
#endif