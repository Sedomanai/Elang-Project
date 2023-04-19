#include "../elpch.h"
#include "aabb.h"

namespace el
{
    void aabb::roundCorners() {
        l = round(l);
        r = round(r);
        b = round(b);
        t = round(t);
    }
    void aabb::halfRoundCorners() {
        l = round(l + 0.5f) - 0.5f;
        r = round(r + 0.5f) - 0.5f;
        t = round(t + 0.5f) - 0.5f;
        b = round(b + 0.5f) - 0.5f;
    } 

    void aabb::halfRoundHorizontalCorners() {
        l = round(l + 0.5f) - 0.5f;
        r = round(r + 0.5f) - 0.5f;
    }
    void aabb::halfRoundVerticalCorners() {
        t = round(t + 0.5f) - 0.5f;
        b = round(b + 0.5f) - 0.5f;
    }
    void aabb::roundHorizontalCorners() {
        l = round(l);
        r = round(r);
    }
    void aabb::roundVerticalCorners() {
        b = round(b);
        t = round(t);
    }
    aabb aabb::copy(const vec2& offset) {
        return aabb(l + offset.x, b + offset.y, r + offset.x, t + offset.y);
    }
}