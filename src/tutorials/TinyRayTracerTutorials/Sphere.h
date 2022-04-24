#include "Aliases.h"
#include <glm/vec3.hpp>

#ifndef SPHERE
#define SPHERE

namespace TinyRayTracerTutorials
{
    struct Sphere
    {
        private:
            Vector3 center;
            float radius;
            
        public:
            Sphere(
                const Vector3& center,
                const float& radius);

            //C++ plebs have no properties so we'll just make get/set methods instead
            Vector3 GetCenter() const;
            float GetRadius() const;

            //First two arguments are not expected to be changed during the method execution, that's why they're marked as const
            
            //The last argument however may (and will) change. More though, we want the change to reflect back to the caller
            //so that it acts as an OUT argument in C#. That's why it's presented as an lvalue reference - simply passing a float
            //would result in copying value type and passing the copy instead. Also keep in mind that lvalue references ARE modifiable
            //compared to rvalue references - they MUST be initialized on their declaration however
            
            //const at the end of function declaration means that we can READ any private variable but cannot modify it
            //i.e. the internal state of the object is not modified
            
            //Also, here's a good stackoverflow discussion thread regarding the usage of 'const'
            //https://stackoverflow.com/questions/117293/use-of-const-for-function-parameters
            //Looks like some maniacs just love to spam 'const' to make sure things remain immutable to the limit
            
            bool RayIntersect(
                const Vector3& origin,
                const Vector3& direction,
                float& distanceToSphere) const;
    };
}

#endif