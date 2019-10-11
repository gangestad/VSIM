#ifndef COLLISION_H
#define COLLISION_H

#include "gsl_math.h"

typedef gsl::Vector3D vec3;

class Collision {
public:
    Collision();
    vec3 barycentricCoordinates(const vec3 &point, const vec3 &pointA, const vec3 &pointB, const vec3 &pointC);
    vec3 getBallNormal(const vec3 &ballPos, std::vector<vec3> surface);
};

#endif // COLLISION_H
