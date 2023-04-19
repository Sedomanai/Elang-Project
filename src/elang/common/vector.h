/*****************************************************************//**
 * @file   vector.h
 * @brief  Vector, using std::vector.
 *		   I separated the interface because there's a chance I may use another vector than std.
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_VECTOR_H
#define  EL_VECTOR_H
#include <vector>

namespace el
{
	/** @typedef vector @brief Type alias for @c std::vector<T>. */
	template <typename T>
	using vector = std::vector<T>;
}

#endif