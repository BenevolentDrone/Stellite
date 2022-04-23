#include "SphereObject.h"

namespace TinyRayTracerTutorials
{
    SphereObject::SphereObject(
        const Sphere& sphere,
        const Material& material)
        : sphere(sphere), material(material) 
    {}

    Sphere SphereObject::GetSphere()
    {
        return sphere;
    }
    
    Material SphereObject::GetMaterial()
    {
        return material;
    }
}