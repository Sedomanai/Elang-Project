#include "../elpch.h"
#include "transform2d.h"

namespace el
{
	Transform2d::Transform2d() :
		tx(0.0f), ty(0.0f), tz(0.0f),
		rx(1.0f), ry(0.0f),
		ux(0.0f), uy(1.0f),
		sx(1.0f), sy(1.0f),
		ez(0.0f) {};

	Transform2d::Transform2d(float tx_, float ty_, float tz_, float rx_, float ry_, float ux_, float uy_, float sx_, float sy_, float ez_) :
		tx(tx_), ty(ty_), tz(tz_),
		rx(rx_), ry(ry_),
		ux(ux_), uy(uy_),
		sx(sx_), sy(sy_), 
		ez(ez_) {};

	Transform2d Transform2d::operator*(const Transform2d& v) const {
		return Transform2d(
			rx * v.tx + ux * v.ty + tx,
			ry * v.tx + uy * v.ty + ty,
			tz + v.tz,

			rx * v.rx + ux * v.ry,
			ry * v.rx + uy * v.ry,

			rx * v.ux + ux * v.uy,
			ry * v.ux + uy * v.uy,

			sx * v.sx, sy * v.sy,
			ez + v.ez
		);
	}

	void Transform2d::to(float x, float y) {
		tx = x; 
		ty = y;
	}
	void Transform2d::move(float x, float y) {
		tx += x;
		ty += y;
	}

	void Transform2d::scale(float x, float y) {
		if (x == 0.0f)
			x = 0.00001f;
		if (y == 0.0f)
			y = 0.00001f;

		rx *= x;
		ry *= x;

		ux *= y;
		uy *= y;

		sx *= x;
		sy *= y;
	}

	void Transform2d::resize(float x, float y) {
		if (x == 0.0f)
			x = 0.00001f;
		if (y == 0.0f)
			y = 0.00001f;

		x /= sx;
		y /= sy;

		rx *= x;
		ry *= x;

		ux *= y;
		uy *= y;

		sx *= x;
		sy *= y;
	}

	void Transform2d::rotate(float degrees) {
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
	}

	void Transform2d::toX(float value) { tx = value; }
	void Transform2d::toY(float value) { ty = value; }
	void Transform2d::toZ(float value) { tz = value; }
	void Transform2d::resizeX(float value) {
		value = (value == 0.0f) ? 0.0001f : value;
		value /= sx;
		rx *= value;
		ry *= value;
		sx *= value;
	}
	void Transform2d::resizeY(float value) {
		value = (value == 0.0f)? 0.0001f : value;
		value /= sy;
		ux *= value;
		uy *= value;
		sy *= value;
	}
	void Transform2d::rotateTo(float degrees) {
		rotate(degrees - ez);
		ez = degrees;
	}
};
