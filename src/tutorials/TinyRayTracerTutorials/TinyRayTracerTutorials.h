#include "Aliases.h"
#include "Sphere.h"
#include "Material.h"
#include "SphereObject.h"

namespace TinyRayTracerTutorials
{
    void BasicRenderToTexture();
    
    void RenderSimpleSphereCast(const Sphere& sphere);
    
    void RenderSphereCastWithMaterials(const List<SphereObject>& spheres);
    
    Vector3 CastRay(
        const Vector3& origin,
        const Vector3& direction,
        const Sphere& sphere);
    
    Vector3 CastRay(
        const Vector3 &origin,
        const Vector3 &direction,
        const List<SphereObject> &spheres);
}