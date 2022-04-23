#include "Sphere.h"
#include <glm/ext.hpp>

namespace TinyRayTracerTutorials
{
    Sphere::Sphere(
        const Vector3& center,
        const float& radius)
        : center(center), radius(radius) 
    {}

    Vector3 Sphere::GetCenter()
    {
        return center;
    }
    
    float Sphere::GetRadius()
    {
        return radius;
    }

    //Dear author of tinyraycaster tutorial,
    
    //1. Stop writing such shitty structs that implicitly return float result for vector multiplication operation
    //If you want to do dot, make a dot function and call it instead. If you want to do magnitude, make a magnitude and call it instead
    
    //2. Start using open source math libs instead of writing shitty structs. Start teaching people to do things right from the get go
    
    //3. If you include a link to some third party resource then either ensure it's livid or include its contents into docs
    //I'll do the former:
    //https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
    
    //4. Start naming variables in a meaningful way. Instead of making the code work I spent my time on useless googling just to 
    //understand what all those L's, tca's and t0's meant. The best UX is to have things right where people need it, not 
    //two hyperlinks and two page readings away - this ruins the entire momentum and thought process
    
    //5. Stop placing variables implicitly among various classes and skipping this part in the tutorial. One source file from your
    //repo contained the declaration of fov equal to 1.05 and the other one had it equal to PI / 2. I (and I believe, many other too)
    //have ZERO will or determination to roam around various repos, their brainches and files within them only to find specific
    //declarations. Tutorials are meant to SAVE time, not to specify how to spend it
    
    bool Sphere::RayIntersect(
        const Vector3& origin,
        const Vector3& direction,
        float& distanceToSphere) const
    {
        Vector3 vectorFromOriginToCenter = center - origin;
        
        float originToCenterProjectionLength = glm::dot(vectorFromOriginToCenter, direction);
        
        float distanceOriginToCenter = glm::length(vectorFromOriginToCenter);
        
        float distanceDirectionVectorToCenterSquared = 
            distanceOriginToCenter * distanceOriginToCenter 
            - originToCenterProjectionLength * originToCenterProjectionLength;
        
        if (distanceDirectionVectorToCenterSquared > radius * radius)
            return false;
        
        float halfPenetrationLength = sqrtf(radius * radius - distanceDirectionVectorToCenterSquared);
        
        distanceToSphere = originToCenterProjectionLength - halfPenetrationLength;
        
        float distanceToSphereOuterShell = originToCenterProjectionLength + halfPenetrationLength;
        
        if (distanceToSphere < 0)
            distanceToSphere = distanceToSphereOuterShell;
        
        if (distanceToSphere < 0)
            return false;
        
        return true;
    }
}