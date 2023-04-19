/*****************************************************************//**
 * @file   transform.h
 * @brief  Transform. For more info check the Transform comment documentaiton
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_TRANSFORM_H
#define  EL_TRANSFORM_H
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "aabb.h"

namespace el
{
    struct vec2;
    struct aabb;
    struct matrix4x4;
    /**
     * @brief Transform is not a matrix4x4. Rather it uses abbreviated calculations for game related geometric transformations. 
     * This makes Transform a somewhat faster alternative to @ref matrix4x4 (at the expense of 8 more bytes of memory).
     * Neither is optimized by SIMD at the moment
     */
	struct Transform
	{
        Transform();
        Transform(
            float tx_, float ty_, float tz_,
            float rx_, float ry_, float rz_,
            float ux_, float uy_, float uz_,
            float fx_, float fy_, float fz_,
            float sx_, float sy_, float sz_,
            float ex_, float ey_, float ez_);

        constexpr vec3 position() const;
        constexpr vec3 scale() const;
        constexpr vec3 euler() const;
        // Unscaled side. Useful to normalize and get direction only
        constexpr vec3 rawSide() const;
        // Unscaled side. Useful to normalize and get direction only
        constexpr vec3 rawUp() const;
        // Unscaled side. Useful to normalize and get direction only
        constexpr vec3 rawFront() const;
        constexpr vec3 side() const;
        constexpr vec3 up() const;
        constexpr vec3 front() const;

        constexpr vec4 operator*(const vec4& v) const;
        constexpr vec3 operator*(const vec3& v) const;
        constexpr vec2 operator*(const vec2& v) const;
        constexpr aabb operator*(const aabb& a) const;
        Transform operator*(const Transform& v) const;

        /**
         * @brief Multiplying a vector by a transform then an inversed transform results in the same vector
         */
        Transform inversed() const;
        void to(float x_, float y_, float z_);
        void to(const vec3& target);
        void move(float x_, float y_, float z_);
        void move(const vec3& delta);
        void scale(vec3 delta);
        void resize(vec3 value);
        void resize(float x, float y, float z);
        void rotate(const vec3& rot);
        void rotateX(float degrees);
        void rotateY(float degrees);
        void rotateZ(float degrees);
        void lookAt(const vec3& target);

        void toX(float value);
        void toY(float value);
        void toZ(float value);
        void resizeX(float value);
        void resizeY(float value);
        void resizeZ(float value);
        void rotateTo(const vec3& rotation);
        void rotateTo(float x, float y, float z);
        void rotateToX(float value);
        void rotateToY(float value);
        void rotateToZ(float value);

        matrix4x4 matrix();
        matrix4x4 inversedMatrix();

        /**
         * Used by Cereal
         *
         * @param archive : InArchive / OutArchive
         */
        template<typename T>
        void serialize(T& archive) {
            archive(tx, ty, tz, rx, ry, rz, ux, uy, uz, fx, fy, fz, sx, sy, sz, ex, ey, ez);
        }

	private:
		float tx, ty, tz;
        float rx, ry, rz;
		float ux, uy, uz;
		float fx, fy, fz;
        float sx, sy, sz;
        float ex, ey, ez;
	};

    constexpr vec3 Transform::position() const { return vec3(tx, ty, tz); }
    constexpr vec3 Transform::scale() const { return vec3(sx, sy, sz); }
    constexpr vec3 Transform::euler() const { return vec3(ex, ey, ez); }
    // Unscaled side. Useful to normalize and get direction only
    constexpr vec3 Transform::rawSide() const { return vec3(rx, ry, rz); }
    // Unscaled side. Useful to normalize and get direction only
    constexpr vec3 Transform::rawUp() const { return vec3(ux, uy, uz); }
    // Unscaled side. Useful to normalize and get direction only
    constexpr vec3 Transform::rawFront() const { return vec3(fx, fy, fz); }
    constexpr vec3 Transform::side() const { return vec3(rx / sx, ry / sx, rz / sx); }
    constexpr vec3 Transform::up() const { return vec3(ux / sy, uy / sy, uz / sy); }
    constexpr vec3 Transform::front() const { return vec3(fx / sz, fy / sz, fz / sz); }


    constexpr vec4 Transform::operator*(const vec4& v) const {
        return vec4(
            rx * v.x + ux * v.y + fx * v.z + tx * v.w,
            ry * v.x + uy * v.y + fy * v.z + ty * v.w,
            rz * v.x + uz * v.y + fz * v.z + tz * v.w,
            v.w
        );
    }
    constexpr vec3 Transform::operator*(const vec3& v) const {
        return vec3(
            rx * v.x + ux * v.y + fx * v.z + tx,
            ry * v.x + uy * v.y + fy * v.z + ty,
            rz * v.x + uz * v.y + fz * v.z + tz
        );
    }
    constexpr vec2 Transform::operator*(const vec2& v) const {
        return vec2(
            rx * v.x + ux * v.y + fx + tx,
            ry * v.x + uy * v.y + fy + ty
        );
    }
    constexpr aabb Transform::operator*(const aabb& a) const {
        vec2 lb = operator*(vec2(a.l, a.b));
        vec2 rt = operator*(vec2(a.r, a.t));
        return aabb(lb.x, lb.y, rt.x, rt.y);
    }
};
#endif