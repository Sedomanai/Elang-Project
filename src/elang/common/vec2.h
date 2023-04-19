/*****************************************************************//**
 * @file   math.h
 * @brief  Math collection
 * 
 * @author Sedomanai
 * @date   September 2022
 *********************************************************************/
#ifndef  EL_VEC2_H
#define  EL_VEC2_H
#include "math.h"

namespace el
{
    struct vec3;
    struct vec4;

    /**
     * @brief Custom vector2 type.
     * 
     * Comments for most methods pending. Too much work for something so obvious.
     */
    struct vec2
    {
        float x, y;

        constexpr vec2();
        constexpr vec2(float common);
        constexpr vec2(float x_, float y_);
        constexpr vec2(const vec2& v);
        constexpr vec2(const vec3& v);
        constexpr vec2(const vec4& v);

        constexpr vec2& operator=(const vec2& v);
        constexpr vec2& operator+=(const vec2& v);
        constexpr vec2& operator+=(const vec3& v);
        constexpr vec2& operator+=(const vec4& v);
        constexpr vec2& operator-=(const vec2& v);
        constexpr vec2& operator-=(const vec3& v);
        constexpr vec2& operator-=(const vec4& v);
        constexpr vec2& operator*=(const vec2& v);
        constexpr vec2& operator*=(const float v);
        constexpr vec2& operator/=(const float v);
        constexpr bool operator==(const vec2& v);
        constexpr bool operator!=(const vec2& v);
        constexpr vec2 operator+(const vec2& v) const;
        constexpr vec2 operator-(const vec2& v) const;
        constexpr vec2 operator*(const float v) const;
        constexpr vec2 operator/(const float v) const;
        constexpr vec2 operator-() const;
        constexpr bool isZero() const;
        constexpr bool isOne() const;
        constexpr float magnitude() const;
        constexpr float	magnitudeSquared() const;
        constexpr float distanceFrom(const vec2& ent) const;

        /**
         * @ref distanceFrom(const vec2&)<float> without square root. 
         * Great for distance comparisons without in need of actual distance value.
         *
         * @param ent Distance from this vector point to this vector.
         * @return Squared value of distance in float/
         */
        constexpr float squaredDistanceFrom(const vec2& ent) const;

        /**
         * Creates new vector with normalized value.
         *
         * @return Normalized new vector
         */
        constexpr vec2 normalized() const;
        /**
         * @brief Normalizes this vector. Value before normalization is lost.
         */
        void normalize();

        template<typename T>
        void serialize(T& archive) {
            archive(x, y);
        }
    };
}

#include "vec3.h"
#include "vec4.h"

namespace el {
    inline constexpr vec2::vec2() : x(0), y(0) {};
    inline constexpr vec2::vec2(float common) : x(common), y(common) {};
    inline constexpr vec2::vec2(float x_, float y_) : x(x_), y(y_) {}
    inline constexpr vec2::vec2(const vec2& v) : x(v.x), y(v.y) {};
    inline constexpr vec2::vec2::vec2(const vec3& v) : x(v.x), y(v.y) {};
    inline constexpr vec2::vec2::vec2(const vec4& v) : x(v.x), y(v.y) {};
#define ELMATH_GLOBAL_FRONT_2D vec2(1, 0)
#define ELMATH_GLOBAL_UP_2D vec2(0, 1)

    inline constexpr vec2& vec2::operator=(const vec2& v) {
        x = v.x; y = v.y;
        return *this;
    }
    inline constexpr vec2& vec2::operator+=(const vec2& v) {
        x += v.x; y += v.y;
        return *this;
    }
    inline constexpr vec2& vec2::operator+=(const vec3& v) {
        x += v.x; y += v.y;
        return *this;
    }
    inline constexpr vec2& vec2::operator+=(const vec4& v) {
        x += v.x; y += v.y;
        return *this;
    }
    inline constexpr vec2& vec2::operator-=(const vec2& v) {
        x -= v.x; y -= v.y;
        return *this;
    }
    inline constexpr vec2& vec2::operator-=(const vec3& v) {
        x -= v.x; y -= v.y;
        return *this;
    }
    inline constexpr vec2& vec2::operator-=(const vec4& v) {
        x -= v.x; y -= v.y;
        return *this;
    }
    inline constexpr bool vec2::operator==(const vec2& v) {
        return x == v.x && y == v.y;
    }
    inline constexpr bool vec2::operator!=(const vec2& v) {
        return x != v.x || y != v.y;
    }
    inline constexpr vec2& vec2::operator*=(const vec2& v) {
        x *= v.x; y *= v.y;
        return *this;
    }
    inline constexpr vec2& vec2::operator*=(const float v) {
        x *= v; y *= v;
        return *this;
    }
    inline constexpr vec2& vec2::operator/=(const float v) {
        x /= v; y /= v;
        return *this;
    }
    inline constexpr vec2 vec2::operator+(const vec2& v) const {
        return vec2(x + v.x, y + v.y);
    }
    inline constexpr vec2 vec2::operator-(const vec2& v) const {
        return vec2(x - v.x, y - v.y);
    }
    inline constexpr vec2 vec2::operator*(const float v) const {
        return vec2(x * v, y * v);
    }
    inline constexpr vec2 vec2::operator/(const float v) const {
        return vec2(x / v, y / v);
    }
    inline constexpr vec2 vec2::operator-() const {
        return vec2(-x, -y);
    }
    inline constexpr bool vec2::isZero() const {
        return x == 0.0f && y == 0.0f;
    }
    inline constexpr bool vec2::isOne() const {
        return x == 1.0f && y == 1.0f;
    }
    inline constexpr float vec2::magnitude() const {
        return math::sqrt(x * x + y * y);
    }
    inline constexpr float	vec2::magnitudeSquared() const {
        return x * x + y * y;
    }
    inline constexpr float vec2::distanceFrom(const vec2& ent) const {
        float dx = x - ent.x;
        float dy = y - ent.y;
        return math::sqrt(dx * dx + dy * dy);
    }
    inline constexpr float vec2::squaredDistanceFrom(const vec2& ent) const {
        float dx = x - ent.x;
        float dy = y - ent.y;
        return dx * dx + dy * dy;
    }
    inline constexpr vec2 vec2::normalized() const {
        if (x != 0.0f && y != 0.0f) {
            float mag = 1.0f / math::sqrt(x * x + y * y);
            return vec2(x * mag, y * mag);
        }
        else return vec2();
    }
    inline void vec2::normalize() {
        if (x != 0.0f && y != 0.0f) {
            float mag = 1.0f / math::sqrt(x * x + y * y);
            x *= mag; y *= mag;
        }
    }
}


#endif