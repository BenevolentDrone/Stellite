#include "../tutorials/SDL/SDLTutorials.h"
#include "../tutorials/TinyRayTracerTutorials/TinyRayTracerTutorials.h"
#include <glm/vec3.hpp>

int main(int, char**) 
{
    //SDLTutorials::BasicWindow();
    
    //TinyRayTracerTutorials::BasicRenderToTexture();
    
    TinyRayTracerTutorials::Sphere sphere(glm::vec3(-3.f, 0.f, -16.f), 2.f);
    TinyRayTracerTutorials::RenderSimpleSphereCast(sphere);
    
    return 0;
}