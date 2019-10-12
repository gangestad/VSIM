#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "octahedronball.h"
class Collision;
class TriangleSurface;

class RollingBall : public OctahedronBall
{
public:
    RollingBall();
    vec3 velocity() const;
    void update(TriangleSurface *obj);

private:
    vec3 mVelocity{0};
    vec3 lastNormal;
    vec3 mAcceleration{0};
    float mSpeed{0.016f};
    vec3 gravity{0.0f, -9.81f, 0.0f};

    void calculateVelocity(vec3 normal, vec3 distanceToTriangle);
    Collision *col;
};

#endif // ROLLINGBALL_H
