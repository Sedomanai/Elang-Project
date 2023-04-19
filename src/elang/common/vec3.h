/*****************************************************************//**
 * @file   math.h
 * @brief  Math collection
 * 
 * @author Sedomanai
 * @date   September 2022
 *********************************************************************/
#ifndef  EL_VEC3_H
#define  EL_VEC3_H

#include "math.h"

namespace el
{
    struct vec2;
    struct vec4;
    /**
     * @brief Custom vector3 type.
     *
     * Comments for most methods pending. Too much work for something so obvious.
     */
    struct vec3
    {
        float x, y, z;

        constexpr vec3();
        constexpr vec3(float common);
        constexpr vec3(float x_, float y_, float z_);
        constexpr vec3(const vec3& v);
        constexpr vec3(const vec2& v, float z_);
        constexpr vec3(const vec4& v);

        constexpr vec3& operator=(const vec3& v);
        constexpr vec3& operator+=(const vec3& v);
        constexpr vec3& operator+=(const vec2& v);
        constexpr vec3& operator+=(const vec4& v);
        constexpr vec3& operator-=(const vec3& v);
        constexpr vec3& operator-=(const vec2& v);
        constexpr vec3& operator-=(const vec4& v);
        constexpr vec3& operator*=(const float v);
        constexpr vec3& operator*=(const vec3& v);
        constexpr vec3& operator/=(const float v);
        constexpr bool operator==(const vec3& v);
        constexpr bool operator!=(const vec3& v);
        constexpr vec3 operator+(const vec3& v) const;
        constexpr vec3 operator-(const vec3& v) const;
        constexpr vec3 operator*(const float v) const;
        constexpr vec3 operator*(const vec3& v) const;
        constexpr vec3 operator/(const float v) const;
        constexpr vec3 operator^(const vec3& v) const;
        constexpr vec3 operator-() const;
        constexpr bool isZero() const;
        constexpr bool isOne() const;
        constexpr float magnitude() const;
        constexpr float	magnitudeSquared() const;
        constexpr float distanceFrom(const vec3& ent) const;

        /**
         * distanceFrom method without square root. Great for distance comparisons without in need of actual distance value.
         *
         * @param ent- Distance from this vector point to this vector
         * @return Squared value of distance in float
         */
        constexpr float squaredDistanceFrom(const vec3& ent) const;

        /**
         * Creates new vector with normalized value.
         *
         * @return Normalized new vector
         */
        constexpr vec3 normalized() const;

        /**
         * @brief Normalizes this vector. Value before normalization is lost.
         */
        void normalize();

        /**
         * @brief If any of the axis is 0, increment by a very small amount to make it non-zero 
         */
        void preventZero();

        /**
         * @return Quaternion of this vector in vec4
         */
        vec4 quaternion() const;

        /**
         * For Cereal.
         *
         * @param Cereal InArchive
         */
        template<typename T>
        void serialize(T& archive) {
            archive(x, y, z);
        }
    };
}

#include "vec2.h"
#include "vec4.h"

namespace el {
    inline constexpr vec3::vec3() : x(0), y(0), z(0) {};
    inline constexpr vec3::vec3(float common) : x(common), y(common), z(common) {};
    inline constexpr vec3::vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};
    inline constexpr vec3::vec3(const vec2& v, float z_) : x(v.x), y(v.y), z(z_) {};
    inline constexpr vec3::vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}
    inline constexpr vec3::vec3(const vec4& v) : x(v.x), y(v.y), z(v.z) {};
#define ELMATH_GLOBAL_SIDE vec3(1, 0, 0)
#define ELMATH_GLOBAL_UP vec3(0, 1, 0)
#define ELMATH_GLOBAL_FRONT vec3(0, 0, 1)

    inline constexpr vec3& vec3::operator=(const vec3& v) {
        x = v.x; y = v.y; z = v.z;
        return *this;
    }
    inline constexpr vec3& vec3::operator+=(const vec3& v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    inline constexpr vec3& vec3::operator+=(const vec2& v) {
        x += v.x; y += v.y;
        return *this;
    }
    inline constexpr vec3& vec3::operator+=(const vec4& v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    inline constexpr vec3& vec3::operator-=(const vec3& v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    inline constexpr vec3& vec3::operator-=(const vec2& v) {
        x -= v.x; y -= v.y;
        return *this;
    }
    inline constexpr vec3& vec3::operator-=(const vec4& v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    inline constexpr vec3& vec3::operator*=(const float v) {
        x *= v; y *= v; z *= v;
        return *this;
    }
    inline constexpr bool vec3::operator==(const vec3& v) {
        return x == v.x && y == v.y && z == v.z;
    }
    inline constexpr bool vec3::operator!=(const vec3& v) {
        return x != v.x || y != v.y || z != v.z;
    }
    inline constexpr vec3& vec3::operator*=(const vec3& v) {
        x *= v.x; y *= v.y; z *= v.z;
        return *this;
    }
    inline constexpr vec3& vec3::operator/=(const float v) {
        x /= v; y /= v; z /= v;
        return *this;
    }
    inline constexpr vec3 vec3::operator+(const vec3& v) const {
        return vec3(x + v.x, y + v.y, z + v.z);
    }
    inline constexpr vec3 vec3::operator-(const vec3& v) const {
        return vec3(x - v.x, y - v.y, z - v.z);
    }
    inline constexpr vec3 vec3::operator*(const float v) const {
        return vec3(x * v, y * v, z * v);
    }
    inline constexpr vec3 vec3::operator*(const vec3& v) const {
        return vec3(x * v.x, y * v.y, z * v.z);
    }
    inline constexpr vec3 vec3::operator^(const vec3& v) const {
        return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
    inline constexpr vec3 vec3::operator/(const float v) const {
        return vec3(x / v, y / v, z / v);
    }
    inline constexpr vec3 vec3::operator-() const {
        return vec3(-x, -y, -z);
    }
    inline constexpr bool vec3::isZero() const {
        return x == 0.0f && y == 0.0f && z == 0.0f;
    }
    inline constexpr bool vec3::isOne() const {
        return x == 1.0f && y == 1.0f && z == 1.0f;
    }
    inline constexpr float vec3::magnitude() const {
        return math::sqrt(x * x + y * y + z * z);
    }
    inline constexpr float	vec3::magnitudeSquared() const {
        return x * x + y * y + z * z;
    }
    inline constexpr float vec3::distanceFrom(const vec3& ent) const {
        float dx = x - ent.x;
        float dy = y - ent.y;
        float dz = z - ent.z;
        return math::sqrt(dx * dx + dy * dy + dz * dz);
    }

    /**
    * distanceFrom method without square root. Great for distance comparisons without in need of actual distance value.
    *
    * @param ent- Distance from this vector point to this vector
    * @return Squared value of distance in float
    */
    inline constexpr float vec3::squaredDistanceFrom(const vec3& ent) const {
        float dx = x - ent.x;
        float dy = y - ent.y;
        float dz = z - ent.z;
        return dx * dx + dy * dy + dz * dz;
    }

    /**
    * Creates new vector with normalized value.
    *
    * @return Normalized new vector
    */
    inline constexpr vec3 vec3::normalized() const {
        if (x != 0.0f || y != 0.0f || z != 0.0f) {
            float mag = 1.0f / sqrt(x * x + y * y + z * z);
            return vec3(x * mag, y * mag, z * mag);
        }
        else return vec3();
    }

    /**
    * Normalizes this vector. Value before normalization is lost.
    */
    inline void vec3::normalize() {
        if (x != 0.0f || y != 0.0f || z != 0.0f) {
            float mag = 1.0f / sqrt(x * x + y * y + z * z);
            x *= mag; y *= mag; z *= mag;
        }
    }
    inline void vec3::preventZero() {
        if (x == 0.0f)
            x = 0.00001f;
        if (y == 0.0f)
            y = 0.00001f;
        if (z == 0.0f)
            z = 0.00001f;
    }

    inline vec4 vec3::quaternion() const {
        // -radians(val * 0.5f)
        float rx = -x * math::pi * math::div_360;
        float ry = -y * math::pi * math::div_360;
        float rz = -z * math::pi * math::div_360;

        float cx = cos(rx);
        float sx = sin(rx);
        float cy = cos(ry);
        float sy = sin(ry);
        float cz = cos(rz);
        float sz = sin(rz);

        return vec4(
            sx * cy * cz - cx * sy * sz,
            cx * sy * cz + sx * cy * sz,
            cx * cy * sz - sx * sy * cz,
            cx * cy * cz + sx * sy * sz
        );
    }
}

#endif