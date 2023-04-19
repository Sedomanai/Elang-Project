/*****************************************************************//**
 * @file   random.h
 * @brief  Random related 
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_RANDOM_H
#define  EL_RANDOM_H
#include <random>

namespace el
{
	/** 
	 * @typedef rng
	 * @brief Type alias for @c std::mt19937.
	 * @brief *
	 * @brief *
	 * @brief * HOW TO USE RNG (because I never remember this)
	 * @brief -------------------------------------------------------------
	 * @brief rng r
	 * @brief r.seed(SEED()());
	 * @brief [i/r/ui]rand rand(minv, maxv)
	 * @brief lv = [i/r/ui]rand(r)
	*/
	using rng = std::mt19937;
	/** @typedef irand @brief Type alias for @c std::uniform_int_distribution<int>. */
	using irand = std::uniform_int_distribution<int>;
	/** @typedef uirand @brief Type alias for @c std::uniform_int_distribution<unsigned int>. */
	using uirand = std::uniform_int_distribution<unsigned int>;
	/** @typedef rrand @brief Type alias for @c std::uniform_real_distribution<float>. */
	using rrand = std::uniform_real_distribution<float>;
	/** @typedef SEED @brief Type alias for @c std::random_device.*/
	using SEED = std::random_device;
}
#endif