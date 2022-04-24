#include "SphereObject.h"

namespace TinyRayTracerTutorials
{
    SphereObject::SphereObject(
        const Sphere& sphere,
        const Material& material)
        : sphere(sphere), material(material) 
    {}

    Sphere SphereObject::GetSphere() const
    {
        return sphere;
    }
    
    Material SphereObject::GetMaterial() const
    {
        return material;
    }
}