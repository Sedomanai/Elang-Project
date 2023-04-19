/*****************************************************************//**
 * @file   type_traits.h
 * @brief  Commonly used type traits.(For non C++20)
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_TYPETRAITS_H
#define  EL_TYPETRAITS_H
#include "define.h"

namespace el
{
	/** @tparam T Check if T is a number. */
	template<typename T>
	struct is_num { static constexpr bool value = (std::is_integral_v<T> || std::is_floating_point_v<T>); };
	/** @tparam T Check if T is a char. */
	template<typename T>
	struct is_char { static constexpr bool value = std::is_same_v<T, char>; };

	/** Value type for @ref el::is_num<T>.  @tparam T Check if T is a number.*/
	template <class T>
	constexpr bool is_num_v = is_char<T>::value;
	/** Value type for @ref el::is_char<T>.  @tparam T Check if T is a char.*/
	template <class T>
	constexpr bool is_char_v = is_char<T>::value;

	/** na for TMP. */
	struct na { typedef na type; enum { value = 0 }; };

	/** Type identity for TMP. @tparam T Identity param, default na. */
	template<typename T = na>
	struct identity { typedef T type; };

	/** Value type for @ref el::identity<T>. @tparam T Identity param, default na.*/
	template <class _Ty>
	using identity_t = typename identity<_Ty>::type;
}

#endif