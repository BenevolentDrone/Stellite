#include "Sphere.h"
#include "Material.h"

namespace TinyRayTracerTutorials
{
    struct SphereObject
    {
        private:
            Sphere sphere;
            Material material;
        
        public:
            SphereObject(
                const Sphere& sphere,
                const Material& material);
            
            Sphere GetSphere();
            Material GetMaterial();
    };
}