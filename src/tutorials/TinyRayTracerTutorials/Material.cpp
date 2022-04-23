#include "Material.h"

namespace TinyRayTracerTutorials
{
    Material::Material(const Color& color)
        : diffuseColor(color)
    {}
            
    Material::Material()
        : diffuseColor()
    {}
    
    Color Material::GetDiffuseColor()
    {
        return diffuseColor;
    }
}