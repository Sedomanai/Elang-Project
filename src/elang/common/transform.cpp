#include "../elpch.h"
#include "transform.h"
#include "matrix4x4.h"

namespace el
{	
    Transform::Transform() :
        tx(0.0f), ty(0.0f), tz(0.0f),
        rx(1.0f), ry(0.0f), rz(0.0f),
        ux(0.0f), uy(1.0f), uz(0.0f),
        fx(0.0f), fy(0.0f), fz(1.0f),
        sx(1.0f), sy(1.0f), sz(1.0f),
        ex(0.0f), ey(0.0f), ez(0.0f) {};

    Transform::Transform(
        float tx_, float ty_, float tz_, 
        float rx_, float ry_, float rz_, 
        float ux_, float uy_, float uz_,
        float fx_, float fy_, float fz_,
        float sx_, float sy_, float sz_,
        float ex_, float ey_, float ez_) :
        tx(tx_), ty(ty_), tz(tz_),
        rx(rx_), ry(ry_), rz(rz_),
        ux(ux_), uy(uy_), uz(uz_),
        fx(fx_), fy(fy_), fz(fz_),
        sx(sx_), sy(sy_), sz(sz_), 
        ex(ex_), ey(ey_), ez(ez_) {};

    Transform Transform::operator*(const Transform& v) const {
        return Transform(
            rx * v.tx + ux * v.ty + fx * v.tz + tx,
            ry * v.tx + uy * v.ty + fy * v.tz + ty,
            rz * v.tx + uz * v.ty + fz * v.tz + tz,

            rx * v.rx + ux * v.ry + fx * v.rz,
            ry * v.rx + uy * v.ry + fy * v.rz,
            rz * v.rx + uz * v.ry + fz * v.rz,

            rx * v.ux + ux * v.uy + fx * v.uz,
            ry * v.ux + uy * v.uy + fy * v.uz,
            rz * v.ux + uz * v.uy + fz * v.uz,

            rx * v.fx + ux * v.fy + fx * v.fz,
            ry * v.fx + uy * v.fy + fy * v.fz,
            rz * v.fx + uz * v.fy + fz * v.fz,

            sx * v.sx, sy * v.sy, sz * v.sz,
            ex + v.ex, ey + v.ey, ez + v.ey
        );
    }

    /**
        * @brief Multiplying a vector by a transform then an inversed transform results in the same vector
        */
    Transform Transform::inversed() const {
        auto dx = 1.0f / sx; 
        auto dy = 1.0f / sy; 
        auto dz = 1.0f / sz;

        auto nrx = rx * dx * dx;
        auto nry = ux * dy * dx;
        auto nrz = fx * dz * dx;

        auto nux = ry * dx * dy;
        auto nuy = uy * dy * dy;
        auto nuz = fy * dz * dy;

        auto nfx = rz * dx * dz;
        auto nfy = uz * dy * dz;
        auto nfz = fz * dz * dz;

        return Transform(
            -nrx * tx - nux * ty - nfx * tz,
            -nry * tx - nuy * ty - nfy * tz,
            -nrz * tx - nuz * ty - nfz * tz,
            nrx, nry, nrz,
            nux, nuy, nuz,
            nfx, nfy, nfz,
            dx, dy, dz,
            -ex, -ey, -ez
        );
    }

	void Transform::to(float x_, float y_, float z_) {
        tx = x_;
        ty = y_;
        tz = z_;
	}
    void Transform::to(const vec3& target) {
        tx = target.x;
        ty = target.y;
        tz = target.z;
    }
    void Transform::move(float x_, float y_, float z_) {
        tx += x_;
        ty += y_;
        tz += z_;
    }
    void Transform::move(const vec3& delta) {
        tx += delta.x;
        ty += delta.y;
        tz += delta.z;
    }
		
    void Transform::scale(vec3 delta) {
        delta.preventZero();
        rx *= delta.x;
        ry *= delta.x;
        rz *= delta.x;

        ux *= delta.y;
        uy *= delta.y;
        uz *= delta.y;

        fx *= delta.z;
        fy *= delta.z;
        fz *= delta.z;

        sx *= delta.x;
        sy *= delta.y;
        sz *= delta.z;
    }
    void Transform::resize(vec3 value) {
        value.preventZero();
        value.x /= sx;
        value.y /= sy;
        value.z /= sz;

        rx *= value.x;
        ry *= value.x;
        rz *= value.x;

        ux *= value.y;
        uy *= value.y;
        uz *= value.y;

        fx *= value.z;
        fy *= value.z;
        fz *= value.z;

        sx *= value.x;
        sy *= value.y;
        sz *= value.z;
    }
    void Transform::resize(float x, float y, float z) {
        resize(vec3(x, y, z));
    }

    void Transform::rotate(const vec3& rot) {
        auto q = rot.quaternion();

        float xx = q.x * q.x;
        float xy = q.x * q.y;
        float xz = q.x * q.z;
        float xw = q.x * q.w;

        float yy = q.y * q.y;
        float yz = q.y * q.z;
        float yw = q.y * q.w;

        float zz = q.z * q.z;
        float zw = q.z * q.w;

        rx = (1 - 2 * (yy + zz)) * sx;
        ry = 2 * (xy + zw) * sy;
        rz = 2 * (xz - yw) * sz;

        ux = 2 * (xy - zw) * sx;
        uy = (1 - 2 * (xx + zz)) * sy;
        uz = 2 * (yz + xw) * sz;

        fx = 2 * (xz + yw) * sx;
        fy = 2 * (yz - xw) * sy;
        fz = (1 - 2 * (xx + yy)) * sz;
    }
    void Transform::rotateX(float degrees) {
        ex += degrees;
        auto rad = degrees * math::to_radians;
        float s = sin(rad);
        float c = cos(rad);

        float tpy = ry;
        ry = tpy * c - rz * s;
        rz = tpy * s + rz * c;
        tpy = uy;
        uy = tpy * c - uz * s;
        uz = tpy * s + uz * c;
        tpy = fy;
        fy = tpy * c - fz * s;
        fz = tpy * s + fz * c;
    }
    void Transform::rotateY(float degrees) {
        ey += degrees;
        auto rad = degrees * math::to_radians;
        float s = sin(rad);
        float c = cos(rad);

        float tpx = rx;
        rx = rz * s + tpx * c;
        rz = rz * c - tpx * s;
        tpx = ux;
        ux = uz * s + tpx * c;
        uz = uz * c - tpx * s;
        tpx = fx;
        fx = fz * s + tpx * c;
        fz = fz * c - tpx * s;
    }
    void Transform::rotateZ(float degrees) {
        ez += degrees;
        auto rad = degrees * math::to_radians;
        float s = sin(rad);
        float c = cos(rad);

        float tpx = rx;
        rx = tpx * c - ry * s;
        ry = tpx * s + ry * c;
        tpx = ux;
        ux = tpx * c - uy * s;
        uy = tpx * s + uy * c;
        tpx = fx;
        fx = tpx * c - fy * s;
        fy = tpx * s + fy * c;
    }
    void Transform::lookAt(const vec3& target) {
        vec3 f = (target - vec3(tx, ty, tz)).normalized();
        vec3 r = (vec3(0, 1, 0) ^ f).normalized();
        vec3 u = f ^ r;

        rx = r.x * sx;
        ry = r.y * sx;
        rz = r.z * sx;

        ux = u.x * sy;
        uy = u.y * sy;
        uz = u.z * sy;

        fx = f.x * sz;
        fy = f.y * sz;
        fz = f.z * sz;
    }

    void Transform::toX(float value) {
        tx = value;
    }
    void Transform::toY(float value) {
        ty = value;
    }
    void Transform::toZ(float value) {
        tz = value;
    }
    void Transform::resizeX(float value) {
        value = value == 0 ? 0.0001f : value;
        value /= sx;
        rx *= value;
        ry *= value;
        rz *= value;
        sx *= value;
    }
    void Transform::resizeY(float value) {
        value = value == 0 ? 0.0001f : value;
        value /= sy;
        ux *= value;
        uy *= value;
        uz *= value;
        sy *= value;
    }
    void Transform::resizeZ(float value) {
        value = value == 0 ? 0.0001f : value;
        value /= sz;
        fx *= value;
        fy *= value;
        fz *= value;
        sz *= value;
    }
    void Transform::rotateTo(const vec3& rotation) {
        rotateToX(rotation.x);
        rotateToY(rotation.y);
        rotateToZ(rotation.z);
    }
    void Transform::rotateTo(float x, float y, float z) {
        rotateToX(x);
        rotateToY(y);
        rotateToZ(z);
    }
    void Transform::rotateToX(float value) {
        rotateX(value - ex);
        ex = value;
    }
    void Transform::rotateToY(float value) {
        rotateY(value - ey);
        ey = value;
    }
    void Transform::rotateToZ(float value) {
        rotateZ(value - ez);
        ez = value;
    }

    matrix4x4 Transform::matrix() {
        return matrix4x4(
            rx, ry, rz, 0.0f,
            ux, uy, uz, 0.0f,
            fx, fy, fz, 0.0f,
            tx, ty, tz, 1.0f
        );
    }

    matrix4x4 Transform::inversedMatrix() {
        return matrix4x4(
            rx, ux, fx, 0.0f,
            ry, uy, fy, 0.0f,
            rz, uz, fz, 0.0f,
            -rx * tx - ry * ty - rz * tz, 
            -ux * tx - uy * ty - uz * tz, 
            -fx * tx - fy * ty - fz * tz, 1.0f
        );
    }
};