#include "collision.h"

Collision::Collision() {
}
/**
 * @brief Collision::barycentricCoordinates computes the barycentric coordinates u,v,w for a point with respect to a triangle
 * @param point The point we compute the coordinates for
 * @param pointA Point A of the triangle
 * @param pointB Point B of the triangle
 * @param pointC Point C of the triangle
 * @return
 */
vec3 Collision::barycentricCoordinates(const vec3 &point, const vec3 &pointA, const vec3 &pointB, const vec3 &pointC) {
    vec3 v0 = pointB - pointA;
    vec3 v1 = pointC - pointA;
    vec3 v2 = point - pointA;

    float v0Sqr = v0 * v0;
    float v0Dotv1 = v0 * v1;
    float v1Sqr = v1 * v1;
    float v2Dotv0 = v2 * v0;
    float v2Dotv1 = v2 * v1;
    float denom = v0Sqr * v1Sqr - v0Dotv1 * v0Dotv1;
    vec3 baryc;
    baryc.setX((v1Sqr * v2Dotv0 - v0Dotv1 * v2Dotv1) / denom);
    baryc.setY((v0Sqr * v2Dotv1 - v0Dotv1 * v2Dotv0) / denom);
    baryc.setZ(1.0f - baryc.getX() - baryc.getY());
    return baryc;
}

// Algoritme: Simulering av rullende ball - Ballsimulering.pdf
// Beregne normalvektor til ballen
vec3 Collision::getBallNormal(const vec3 &ballPos, std::vector<vec3> surface)
{
    vec3 normal;
    for(size_t i = 0; i < surface.size(); i+=3){
        // Check every three surface points for the triangle
        vec3 baryc = barycentricCoordinates(ballPos, surface[i], surface[i+1], surface[i+2]);
        if(baryc.getX() >= 0 && baryc.getY() >= 0 && (baryc.getY() + baryc.getX()) <= 1){
            // Formula(6.2) from .pdf
            normal = (surface[i+1] - surface[i])^(surface[i*2] - surface[i]);
            break;
        }
    }
    return normal.normalized();
}
