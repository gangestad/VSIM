#include "rollingball.h"
#include "collision.h"
#include "trianglesurface.h"

RollingBall::RollingBall()
{
    col = new Collision;
}

void RollingBall::update(TriangleSurface *obj)
{
    auto [hitResult, normal, position] = col->getBallNormal(getPosition(), obj);
    if(hitResult){
        calculateVelocity(normal, position);
        move((getPosition() + velocity()));
    }
}

vec3 RollingBall::velocity() const{
    return mVelocity;
}

void RollingBall::calculateVelocity(vec3 normal, vec3 vectorToTriangle)
{

        vec3 N = normal * vec3::dot(gravity, normal);
        float distanceToTriangle = vec3::dot(getPosition() - vectorToTriangle, normal);

        if(distanceToTriangle > radius()){
            normal = vec3(0);
            N = vec3(0);
        }else{
            float distance = radius() - distanceToTriangle;
            if(distance > 0.2f){
                getModelMatrix().translate(normal * distance);
            }
            if(normal != lastNormal){
                if(normal == vec3(0)){
                } else if (lastNormal == vec3(0)){
                    mVelocity = (gravity + N).normalized() * vec3::dot(velocity(), (gravity+N).normalized());
                } else {
                    vec3 tempNormal = normal + lastNormal;
                    tempNormal.normalize();
                    vec3 tempVelocity = tempNormal * vec3::dot(velocity(), tempNormal);
                    mVelocity = velocity() - tempVelocity * 2;
                    mVelocity = tempVelocity;
                }
            }
            lastNormal = normal;
            mAcceleration = (N+gravity);
            mVelocity += mAcceleration * mSpeed;
        }
}



