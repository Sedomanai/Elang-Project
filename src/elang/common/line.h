/*****************************************************************//**
 * @file   line.h
 * @brief  2D line segment
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_LINE_H
#define  EL_LINE_H
#include "vec2.h"

namespace el
{
	struct stream;
	/**
	 * @brief Line between 2 points with x,y coordinates.
	 * Actually made of four floats instead of 2 @ref vec2.
	 */
	struct line
	{
		/** Line constructor. Resets both coordinates to 0 0.*/
		constexpr line() : p1x(0.0f), p1y(0.0f), p2x(0.0f), p2y(0.0f) {}
		/**
		 * Line constructor. 
		 * @param p1x_ x value of point 1. 
		 * @param p1y_ y value of point 1. 
		 * @param p2x_ x value of point 2. 
		 * @param p2y_ y value of point 2. 
		 */
		constexpr line(float p1x_, float p1y_, float p2x_, float p2y_)
			: p1x(p1x_), p1y(p1y_), p2x(p2x_), p2y(p2y_) {};;

		/** First point. @return Coordinate of first point in @ref vec2 (x,y)*/
		constexpr vec2 p1() const { return vec2(p1x, p1y); };
		constexpr vec2 p2() const { return vec2(p2x, p2y); };

		/**
		 * Used by Cereal. Do not bother.
		 *
		 * @param archive : InArchive/OutArchive
		 */
		template<typename T>
		void serialize(T& archive) {
			archive(p1x, p1y, p2x, p2y);
		}

		float p1x, p1y, p2x, p2y;
	};
}
#endif