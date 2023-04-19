/*****************************************************************//**
 * @file   vec4.h
 * @brief  vector4
 * 
 * @author Sedomanai
 * @date   September 2022
 *********************************************************************/
#ifndef  EL_VEC4_H
#define  EL_VEC4_H
#include "math.h"

namespace el
{
    struct vec2;
    struct vec3;    
    
    /**
     * @brief Custom vector4 type.
     *
     * Comments for most methods pending. Too much work for something so obvious.
     */
    struct vec4
    {
        float x, y, z, w;

        constexpr vec4();
        constexpr vec4(float common);
        constexpr vec4(float x_, float y_, float z_, float w_);
        constexpr vec4(const vec4& v);
        constexpr vec4(const vec2& v, float z_, float w_);
        constexpr vec4(const vec3& v, float w_);

        constexpr vec4& operator=(const vec4& v);
        constexpr vec4& operator+=(const vec4& v);
        constexpr vec4& operator+=(const vec2& v);
        constexpr vec4& operator+=(const vec3& v);
        constexpr vec4& operator-=(const vec4& v);
        constexpr vec4& operator-=(const vec2& v);
        constexpr vec4& operator-=(const vec3& v);
        constexpr vec4& operator*=(const float v);
        constexpr vec4& operator*=(const vec4& v);
        constexpr vec4& operator/=(const float v);
        constexpr bool operator==(const vec4& v);
        constexpr bool operator!=(const vec4& v);
        constexpr vec4 operator+(const vec4& v) const;
        constexpr vec4 operator-(const vec4& v) const;
        constexpr vec4 operator*(const float v) const;
        constexpr vec4 operator*(const vec4& v) const;
        constexpr vec4 operator/(const float v) const;
        constexpr vec3 operator-() const;
        constexpr bool isZero() const;
        constexpr bool isOne() const;

        /**
         * For Cereal.
         *
         * @param Cereal InArchive
         */
        template<typename T>
        void serialize(T& archive) {
            archive(x, y, z, w);
        }
    };
}

#include "vec2.h"
#include "vec3.h"
namespace el {
    //impl
    inline constexpr vec4::vec4() : x(0), y(0), z(0), w(0) {};
    inline constexpr vec4::vec4(float common) : x(common), y(common), z(common), w(common) {};
    inline constexpr vec4::vec4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {};
    inline constexpr vec4::vec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    inline constexpr vec4::vec4(const vec2& v, float z_, float w_) : x(v.x), y(v.y), z(z_), w(w_) {};
    inline constexpr vec4::vec4(const vec3& v, float w_) : x(v.x), y(v.y), z(v.z), w(w_) {};

    inline constexpr vec4& vec4::operator=(const vec4& v) {
        x = v.x; y = v.y; z = v.z; w = v.w;
        return *this;
    }
    inline constexpr bool vec4::operator==(const vec4& v) {
        return x == v.x && y == v.y && z == v.z && w == v.w;
    }
    inline constexpr bool vec4::operator!=(const vec4& v) {
        return x != v.x || y != v.y || z != v.z || w == v.w;
    }
    inline constexpr vec4& vec4::operator+=(const vec4& v) {
        x += v.x; y += v.y; z += v.z; w += v.w;
        return *this;
    }
    inline constexpr vec4& vec4::operator+=(const vec2& v) {
        x += v.x; y += v.y;
        return *this;
    }
    inline constexpr vec4& vec4::operator+=(const vec3& v) {
        x += v.x; y += v.y; z += v.z; 
        return *this;
    }
    inline constexpr vec4& vec4::operator-=(const vec4& v) {
        x -= v.x; y -= v.y; z -= v.z; w -= v.w;
        return *this;
    }
    inline constexpr vec4& vec4::operator-=(const vec2& v) {
        x -= v.x; y -= v.y;
        return *this;
    }
    inline constexpr vec4& vec4::operator-=(const vec3& v) {
        x -= v.x; y -= v.y; z -= v.z; 
        return *this;
    }
    inline constexpr vec4& vec4::operator*=(const float v) {
        x *= v; y *= v; z *= v; w *= v;
        return *this;
    }
    inline constexpr vec4& vec4::operator*=(const vec4& v) {
        x *= v.x; y *= v.y; z *= v.z; w *= v.w;
        return *this;
    }
    inline constexpr vec4& vec4::operator/=(const float v) {
        x /= v; y /= v; z /= v; w /= v;
        return *this;
    }
    inline constexpr vec4 vec4::operator+(const vec4& v) const {
        return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    inline constexpr vec4 vec4::operator-(const vec4& v) const {
        return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    inline constexpr vec4 vec4::operator*(const float v) const {
        return vec4(x * v, y * v, z * v, w * v);
    }
    inline constexpr vec4 vec4::operator*(const vec4& v) const {
        return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
    }
    inline constexpr vec4 vec4::operator/(const float v) const {
        return vec4(x / v, y / v, z / v, w / v);
    }
    inline constexpr vec3 vec4::operator-() const {
        return vec4(-x, -y, -z, -w);
    }
    inline constexpr bool vec4::isZero() const {
        return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
    }
    inline constexpr bool vec4::isOne() const {
        return x == 1.0f && y == 1.0f && z == 1.0f && w == 1.0f;
    }
}
#endif