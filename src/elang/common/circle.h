/*****************************************************************//**
 * @file   circle.h
 * @brief  2d circle
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_CIRCLE_H
#define  EL_CIRCLE_H

namespace el
{
	struct vec2;
	/**
	 * @brief Circular bound with position x, y, and radius values
	 */
	struct circle
	{
		/**
		 * @brief Circle constructor.
		 * Coordinate and radius initialized to zero. 
		 */
		inline constexpr circle() : x(0.0f), y(0.0f), r(0.0f) {}

		/**
		 * @brief Circle constructor.
		 * @param x_ X value of center coordinate.
		 * @param y_ Y value of center coordinate.
		 * @param radius Radius of the circle from the center.
		 */
		inline constexpr circle(float x_, float y_, float radius) : x(x_), y(y_), r(radius) {};

		 /** @brief Check if a point is fully contained within this circle. @param point The point to check containment. @return True if point is contained in the circle. */
		bool contains(const vec2& point) const;

		/**
		 * Copies a new circle out of this one.
		 *
		 * @param offset : A new circle in a new position determined by offset value
		 * @return New circle
		 */
		circle copy(const vec2& offset);

		/**
		 * Used by Cereal
		 *
		 * @param InArchive/OutArchive
		 */
		template<typename T>
		void serialize(T& archive) {
			archive(x, y, r);
		}

		float x, y, r;
	};
}
#endif