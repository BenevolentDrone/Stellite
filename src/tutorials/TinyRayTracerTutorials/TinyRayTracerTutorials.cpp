#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "TinyRayTracerTutorials.h"

//First I used a pointer to framebuffer to pass it by reference C#-style. But then I looked at how often the tutorial maker used
//references (and I mean C++ lvalue references) instead so I googled the question. Here is what I found out:
//https://stackoverflow.com/questions/7058339/when-to-use-references-vs-pointers

//Basically, C++ people got tired of those endless ****foobar's, downcasting and checking whether the pointer is null so much they've
//made lvalue references. That kinda makes sence to me because I'm not a huge fan of that stuff either. Still having this many options
//for variable transfer modes utilizing the same symbols in a different manner (like come on, I thought '&' is dereferencing!) is bugging
//me out. I still question the design behind rvalue references but hey - a couple more days researching the stupid shit C++ does compared
//to C# (including those stupid ass CMakes) and I start believing that they make sence too.

void WriteGradient(
    List<Vector3>& framebuffer,
    int width,
    int height)
{
    for (size_t y = 0; y < height; y++) 
    {
        for (size_t x = 0; x < width; x++) 
        {
            framebuffer[x + y * width] = Vector3(
                y / float(height),
                x / float(width),
                0);
        }
    }
}

void SaveBufferToImage(
    List<Vector3>& framebuffer,
    int width,
    int height)
{
    std::ofstream ofs; // save the framebuffer to file
    
    ofs.open("./out.ppm");
    
    ofs << "P6\n" << width << " " << height << "\n255\n";
    
    for (size_t i = 0; i < height * width; ++i) 
    {
        for (size_t j = 0; j < 3; j++) 
        {
            ofs << (char)(255 * std::max(
                0.f,
                std::min(
                    1.f,
                    framebuffer[i][j])));
        }
    }
    
    ofs.close();
}

void TinyRayTracerTutorials::BasicRenderToTexture() 
{
    const int width    = 1024;
    const int height   = 768;
    
    List<Vector3> framebuffer(width * height);

    WriteGradient(framebuffer, width, height);

    SaveBufferToImage(framebuffer, width, height);
}

glm::vec3 TinyRayTracerTutorials::CastRay(
    const Vector3 &orig,
    const Vector3 &dir,
    const Sphere& sphere)
{
    float sphere_dist = std::numeric_limits<float>::max();
    
    if (!sphere.RayIntersect(orig, dir, sphere_dist))
    {
        return Vector3(0.2, 0.7, 0.8); // background color
    }
    
    return Vector3(0.4, 0.4, 0.3); // sphere color
}

void WriteSimpleSphereCast(
    List<Vector3>& framebuffer,
    int width,
    int height,
    float fov,
    const TinyRayTracerTutorials::Sphere& sphere)
{
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            
            float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
            
            Vector3 dir = glm::normalize(glm::vec3(x, y, -1));
            
            framebuffer[i + j * width] = TinyRayTracerTutorials::CastRay(
                Vector3(0, 0, 0),
                dir,
                sphere);
        }
    }
}

void TinyRayTracerTutorials::RenderSimpleSphereCast(const Sphere& sphere) 
{
    const int width = 1024;
    const int height = 768;
    
    const float fov = glm::pi<float>() / 2.f; //1.05; // 60 degrees field of view in radians
    
    List<Vector3> framebuffer(width * height);
    
    WriteSimpleSphereCast(framebuffer, width, height, fov, sphere);

    SaveBufferToImage(framebuffer, width, height);
}