/*****************************************************************//**
 * @file   define.h
 * @brief  Elang common definitions, macros, and 'using' operators.
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_DEFINE_H
#define  EL_DEFINE_H
#include <type_traits>
#include <iostream>
#include <assert.h>

/** @typedef sizet @brief Type alias for @c size_t. */
using sizet = size_t;
/** @typedef int8 @brief Type alias for @c int8_t. */
using int8 = int8_t;
/** @typedef int16 @brief Type alias for @c int16_t. */
using int16 = int16_t;
/** @typedef int32 @brief Type alias for @c int32_t. */
using int32 = int32_t;
/** @typedef int64 @brief Type alias for @c int64_t. */
using int64 = int64_t;
/** @typedef uint @brief Type alias for @c unsigned int. */
using uint = unsigned int;
/** @typedef uint8 @brief Type alias for @c uint8_t. */
using uint8 = uint8_t;
/** @typedef uint16 @brief Type alias for @c uint16_t. */
using uint16 = uint16_t;
/** @typedef uint32 @brief Type alias for @c uint32_t. */
using uint32 = uint32_t;
/** @typedef uint64 @brief Type alias for @c uint64_t. */
using uint64 = uint64_t;

/**
 * Explicit class copy constructor and assignment operator.
 * 
 * Macro for specific use cases, mostly involving EnTT.
 * Does not include destructor.
 * @param t Self type.
 * @param base Base type to inherit from.
 */
#define EL_USING_BASE_CLASS(t, base) \
using base::base; \
t(const base& src) : base::base(src) {} \
t(base&& src) : base::base(src) {} \
t& operator=(const base& src) { base::operator=(src); return *this; } \
t& operator=(base&& src) { base::operator=(src); return *this; }

namespace el
{
	/** @typedef logger @brief Type alias for @c std::ostream. */
	using logger = std::ostream;
}

using std::cout;
using std::cin;
using std::endl;
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX
#endif