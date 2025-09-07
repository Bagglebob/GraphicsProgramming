#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    ray() {}

    ray(const vec::point3& origin, const vec::vec3& direction) : orig(origin), dir(direction) {}

    // returns immutable reference to an object of type point3 (or vec3, since im using an alias)
    // trailing const prevents this function from mutating "this" instance
    const vec::point3& origin() const { return orig; }

    // returns immutable reference to an object of type point3 (or vec3, since im using an alias)
    // trailing const prevents this function from mutating "this" instance
    const vec::vec3& direction() const { return dir; }

    vec::point3 at(double t) const {
        return orig + t * dir;
    }

private:
    vec::point3 orig;
    vec::vec3 dir;
};

#endif