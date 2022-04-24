#include "../tutorials/SDL/SDLTutorials.h"
#include "../tutorials/TinyRayTracerTutorials/TinyRayTracerTutorials.h"
#include <glm/vec3.hpp>

using Sphere = TinyRayTracerTutorials::Sphere;
using Material = TinyRayTracerTutorials::Material;
using SphereObject = TinyRayTracerTutorials::SphereObject;

int main(int, char**) 
{
    //SDLTutorials::BasicWindow();
    
    //TinyRayTracerTutorials::BasicRenderToTexture();
    
    //Sphere sphere(glm::vec3(-3.f, 0.f, -16.f), 2.f);
    //TinyRayTracerTutorials::RenderSimpleSphereCast(sphere);
    
    Material ivory(glm::vec3(0.4, 0.4, 0.3));
    Material red_rubber(glm::vec3(0.3, 0.1, 0.1));

    std::vector<TinyRayTracerTutorials::SphereObject> spheres;
    
    spheres.push_back(
        SphereObject(
            Sphere(glm::vec3(-3, 0, -16), 2),
            Material(ivory)));
    
    spheres.push_back(
        SphereObject(
            Sphere(glm::vec3(-1.0, -1.5, -12), 2),
            Material(red_rubber)));
    
    spheres.push_back(
        SphereObject(
            Sphere(glm::vec3(1.5, -0.5, -18), 3),
            Material(red_rubber)));
    
    spheres.push_back(
        SphereObject(
            Sphere(glm::vec3(7, 5, -18), 4),
            Material(ivory)));

    TinyRayTracerTutorials::RenderSphereCastWithMaterials(spheres);
    
    return 0;
}