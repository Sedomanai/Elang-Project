#include "../elpch.h"
#include "circle.h"
#include "vec2.h"

namespace el
{
    // @return True only if aabb "a" is fully contained within this aabb
    bool circle::contains(const vec2& point) const {
        auto dx = (x - point.x);
        auto dy = (y - point.y);
        return dx * dx + dy * dy < r* r;
    }

    circle circle::copy(const vec2& offset) {
        return circle(x + offset.x, y + offset.y, r);
    }
}