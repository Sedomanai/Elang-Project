/*****************************************************************//**
 * @file   math.h
 * @brief  Math collection
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_MATH_H
#define  EL_MATH_H
#include "define.h"
#include <cfloat>
#include <cmath>

namespace el
{
	namespace math
	{
		/** @typedef d_pi @brief Value of PI in double. */
		inline constexpr double d_pi = 3.14159265358979;
		/** @typedef d_pi @brief Value of PI in float. */
		inline constexpr float pi = 3.14159265359f;
		/** @typedef d_pi @brief Value half of PI in float. */
		inline constexpr float half_pi = d_pi / 2.0f;
		/** @typedef d_pi @brief Value of 1 divided by 180. */
		inline constexpr float div_180 = 1.0f / 180.0f;
		/** @typedef d_pi @brief Value of 1 divided by 360. */
		inline constexpr float div_360 = 1.0f / 360.0f;
		/** @typedef d_pi @brief Value of 1 divided by PI. */
		inline constexpr float div_pi = 1.0f / d_pi;
		/** @typedef d_pi @brief Value of PI divided by 180. Multiply to translate degrees to radians. */
		inline constexpr float to_radians = pi * div_180;
		/** @typedef d_pi @brief Value PI divided by 180. Multiply to translate radians to degrees. */
		inline constexpr float to_degrees = 180.0f * div_pi;

		/**
		 * @brief Normalize an angle. 
		 * Normalize means clamp an angle so that it is >= 0 and <= 360, in degrees.
		 * 
		 * @param Angle to normalize, in degrees.
		 * @param Normalized angle, in degrees.
		 */
		inline float normalizeAngle(float degrees) {
			// reduce the angle  
			degrees = fmod(degrees, 360.f);

			// force it to be the positive remainder, so that 0 <= angle < 360  
			degrees = fmod(degrees + 360.0f, 360.0f);

			// force into the minimum absolute value residue class, so that -180 < angle <= 180  
			if (degrees > 180)
				degrees -= 360;

			return degrees;
		}
		/**
		 * @brief For more loose float comparions.
		 */
		inline bool nearly_equal(float a, float b, float epsilon, float relth) {
			 assert(std::numeric_limits<float>::epsilon() <= epsilon);
			 assert(epsilon < 1.f);

			 if (a == b) return true;

			 auto diff = std::abs(a - b);
			 auto norm = std::min((std::abs(a) + std::abs(b)), std::numeric_limits<float>::max());
			 // or even faster: std::min(std::abs(a + b), std::numeric_limits<float>::max());
			 // keeping this commented out until I update figures below
			 return diff < std::max(relth, epsilon* norm);
		 }

		template<typename T>
		inline T constexpr sqrtNewtonRaphson(T x, T curr, T prev) {
			return curr == prev
				? curr
				: sqrtNewtonRaphson<T>(x, 0.5f * (curr + x / curr), curr);
		}

		/**
		 * @brief Constexpr version of the square root.
		 *
		 * @return For a finite and non-negative value of x, returns an approximation of the square root of x, otherwise, returns NaN
		 */
		template<typename T>
		inline T constexpr sqrt(T x) {
			return x >= 0 && x < std::numeric_limits<T>::infinity()
				? sqrtNewtonRaphson<T>(x, x, 0)
				: std::numeric_limits<T>::quiet_NaN();
		}
	}
}
#endif