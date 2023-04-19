/*****************************************************************//**
 * @file   aabb.h
 * @brief  AABB related
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_AABB_H
#define  EL_AABB_H

namespace el
{
	struct vec2;
	/**
	 * @brief The bounds of a non-transformed rectangle with left, bottom, right, and top values.
	 */
	struct aabb
	{
		/** @brief AABB default constructor. Set all fields to zero. */
		constexpr aabb();
		/** @brief AABB default constructor. @param left Leftmost x. @param bottom Bottommost y. (Implementation independent.) @param right Rightmost x. @param top Topmost y. (Implementation independent.)*/
		constexpr aabb(float left, float bottom, float right, float top);
		/** @brief Get center point coordinate value of aabb. @return @ref vec2 value.*/
		constexpr vec2 center() const;
		/** @brief Get width of aabb, or right - left. @return The width in float value.*/
		constexpr float width() const;
		/** @brief Get height of aabb, or top - bottom. @return The height in float value.*/
		constexpr float height() const;
		/** @brief Get the area of aabb, or @ref width() * @ref height(). @return The height in float value.*/
		constexpr float area() const;
		/** @brief Move aabb to by a specific vector, without affecting its dimensions. @param value Move by the value of @ref vec2. */
		constexpr void move(const vec2& value);
		/**
		 * @brief Normalize aabb.
		 * 
		 * Used to prevent left from being larger than right, or bottom from being larger than top.
		 * (May change the name to prevent confusion..)
		 * 
		 * @warning This function is not called for every changes to the rect that may un-normalize this aabb.
		 * It must be called manually, when it matters.
		 */
		constexpr void normalize();
		// @brief Expands rect by the value on each side (that is, all sides are expanded). @param The value in float to expand by. 
		constexpr void expand(float value);

		/** 
		 * @brief Expands rect by the value on each side(that is, all sides are expanded).
		 * 
		 * Expands by dx horizontally, and dy vertically.
		 * 
		 * @param dx Expand by this value horizontally, on both sides.
		 * @param dy Expand by this value vertically, on both sides.
		 */
		constexpr void expand(float dx, float dy);

		/** @brief Check if a point is fully contained within this aabb. @param point The point to check containment. @return True if point is contained in the aabb. */ 
		constexpr bool contains(const vec2& point) const;
		/** @brief Check if another aabb is fully within the bounds of this aabb. @param aabb The aabb to check containment. @return True if given param is contained in the aabb. */
		constexpr bool contains(const aabb&) const;
		/** @brief Check if another aabb intersects or even just touches the bounds of this aabb @param aabb The aabb to check intersection. @retrurn True if given param intersects the aabb. */
		constexpr bool intersects(const aabb&) const;
		/** @brief The intersection of this aabb and another given aabb. @param aabb The given aabb to intersect. @return Another aabb that is the intersection of this aabb and @p aabb.*/
		constexpr aabb intersected(const aabb&) const;
		/** @brief The union of this aabb and another given aabb. @param aabb The given aabb to unite with. @return Another aabb that is the union of this aabb and @p aabb.*/
		constexpr aabb united(const aabb&) const;

		/** @brief Traps a point within this aabb, uses clamp. @param point The point to trap in @ref vec2; overwrites value of @p point. */
		constexpr void trap(vec2& point);
		/**
		 * @brief Traps an aabb within this aabb, uses clamp.
		 * 
		 * If a dimension of the aabb to trap is smaller than the same dimension of this aabb,
		 * the aabb is snapped to either the left or top (left-top corner).
		 *
		 * @param a : The aabb to trap in vec2, overwrites value
		 */
		constexpr void trap(aabb& a);

		/** @brief Round all corners to the nearest integers. */ 
		void roundCorners();
		/** @brief  Round all corners to the nearest multiples of 0.5 (including negatives) */ 
		void halfRoundCorners();
		/** @brief  Round all corners to the nearest multiples of 0.5 (including negatives), left and right only */ 
		void halfRoundHorizontalCorners();
		/** @brief  Round all corners to the nearest multiples of 0.5 (including negatives), bottom and top only */ 
		void halfRoundVerticalCorners();
		/** @brief  Round to the nearest integers, left and right only */ 
		void roundHorizontalCorners();
		/** @brief  Round to the nearest integers, bottom and top only */ 
		void roundVerticalCorners();

		/**
		 * @brief Copies a new aabb out of this one.
		 *
		 * @param offset A new aabb in a new position determined by offset value.
		 * @return The new aabb, which is offset by the value of param @p offset.
		 */
		aabb copy(const vec2& offset);

		/**
		 * @brief Used by Cereal
		 *
		 * @param archive Type of @p T.
		 * @tparam T Archive Type such as InArchive or OutArchive.
		 */
		template<typename T>
		void serialize(T& archive) {
			archive(l, b, r, t);
		}

		//friend logger& operator<<(logger& log, const aabb& a) {
		//    log << "( " << a.l << ", " << a.b << ", " << a.r << ", " <<  a.t << " )";
		//    return log;
		//}

		float l, b, r, t;
	};
}

#include "vec2.h"
#include "algorithm.h"

namespace el
{
	inline constexpr aabb::aabb() : l(0), b(0), r(0), t(0) {}
	inline constexpr aabb::aabb(float left, float bottom, float right, float top)
		: l(left), b(bottom), r(right), t(top) {}

	inline constexpr vec2 aabb::center() const {
		return vec2((l + r) / 2.0f, (b + t) / 2.0f);
	}
	inline constexpr float aabb::width() const {
		return r - l;
	}
	inline constexpr float aabb::height() const {
		return t - b;
	}
	inline constexpr float aabb::area() const {
		return (r - l) * (t - b);
	}
	inline constexpr void aabb::move(const vec2& value) {
		l += value.x;
		r += value.x;
		b += value.y;
		t += value.y;
	}
	inline constexpr void aabb::normalize() {
		if (r < l) {
			float temp = l;
			l = r;
			r = temp;
		}
		if (t < b) {
			float temp = b;
			b = t;
			t = temp;
		}
	}
	inline constexpr void aabb::expand(float value) { l -= value; r += value; b -= value; t += value; }
	inline constexpr void aabb::expand(float dx, float dy) { l -= dx; r += dx; b -= dy; t += dy; }

	inline constexpr bool aabb::contains(const vec2& point) const {
		return point.x >= l && point.x <= r && point.y >= b && point.y <= t;
	}

	inline constexpr bool aabb::contains(const aabb& a) const {
		return a.l >= l && a.r <= r && a.b >= b && a.t <= t;
	}
	inline constexpr bool aabb::intersects(const aabb& a) const {
		return (a.l <= r && l <= a.r && a.b <= t && b <= a.t);
	}
	inline constexpr aabb aabb::intersected(const aabb& a) const {
		return aabb(l > a.l ? l : a.l, b > a.b ? b : a.b, r < a.r ? r : a.r, t < a.t ? t : a.t);
	}
	inline constexpr aabb aabb::united(const aabb& a) const {
		return aabb(l<a.l ? l : a.l, b < a.b ? b : a.b, r>a.r ? r : a.r, t > a.t ? t : a.t);
	}
	inline constexpr void aabb::trap(vec2& point) {
		point.x = clamp(point.x, l, r);
		point.y = clamp(point.y, b, t);
	}
	inline constexpr void aabb::trap(aabb& a) {
		vec2 val;
		if (a.width() < width()) {
			if (a.l < l)
				val.x = l - a.l;
			if (a.r > r)
				val.x = r - a.r;
		}
		else {
			a.r = l + a.width();
			a.l = l;
		}

		if (a.height() < height()) {
			if (a.b < b)
				val.y = b - a.b;
			if (a.t > t)
				val.y = t - a.t;
		}
		else {
			a.b = t - a.height();
			a.t = t;
		}
		a.move(val);
	}
}

#endif