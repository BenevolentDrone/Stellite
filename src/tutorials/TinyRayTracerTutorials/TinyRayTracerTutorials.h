#include "Sphere.h"
#include "Material.h"
#include <vector>

using Vector3 = glm::vec3;

template<typename TValue>
using List = std::vector<TValue>;

namespace TinyRayTracerTutorials
{
    void BasicRenderToTexture();
    
    void RenderSimpleSphereCast(const Sphere& sphere);
    
    Vector3 CastRay(
        const Vector3& origin,
        const Vector3& direction,
        const Sphere& sphere);
    
    /*
    bool CastRay(
        const Vector3& orig,
        const Vector3& dir,
        const Sphere& sphere,
        const List<Sphere> &spheres,
        Vector3& hit,
        Vector3& N,
        Material &material);
    */
}