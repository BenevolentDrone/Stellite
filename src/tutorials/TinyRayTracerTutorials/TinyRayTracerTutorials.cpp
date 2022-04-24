#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
//#include <vector>
//#include <glm/vec3.hpp>
//#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "TinyRayTracerTutorials.h"

namespace TinyRayTracerTutorials
{
    //First I used a pointer to framebuffer to pass it by reference C#-style. But then I looked at how often the tutorial maker used
    //references (and I mean C++ lvalue references) instead so I googled the question. Here is what I found out:
    //https://stackoverflow.com/questions/7058339/when-to-use-references-vs-pointers

    //Basically, C++ people got tired of those endless ****foobar's, downcasting and checking whether the pointer is null so much they've
    //made lvalue references. That kinda makes sence to me because I'm not a huge fan of that stuff either. Still having this many options
    //for variable transfer modes utilizing the same symbols in a different manner (like come on, I thought '&' is dereferencing!) is bugging
    //me out. I still question the design behind rvalue references but hey - a couple more days researching the stupid shit C++ does compared
    //to C# (including those stupid ass CMakes) and I start believing that they make sence too.

    //Another thing to mention is that in C# i prefer to declare methods in a top-down fashion representing the call hierarchy. Like, here's
    //a public method A that calls B and C while B calls some D method. Then the order of methods would be
    //A() {...}
    //B() {...}
    //D() {...}
    //C() {...}
    //The logic behind it is trivial: if I'm inspecting how method A works then the first method I'd want to investigate after it would be
    //the one I encounter first within its body - the method B(). That way I'm not spending much time scrolling scripts and get where I want
    //the fastest way
    
    //For C++ though this logic has to be fucking inverted because C++ compiler despite being smart enough to operate AST's is stupid enough
    //to think that if something is not defined before the current row then it effectively doesn't exist at all. Thus method A would not know
    //about the method B's existence and start throwing compiler errors upon being compiled. Lo and behold, a programming language in which
    //the order of METHOD DEFINITION affects the compilation

#pragma region Basic render to texture

    void WriteGradientToBuffer(
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

    void BasicRenderToTexture() 
    {
        const int width = 1024;
        const int height = 768;
        
        List<Vector3> framebuffer(width * height);

        WriteGradientToBuffer(framebuffer, width, height);

        SaveBufferToImage(framebuffer, width, height);
    }

#pragma endregion

#pragma region Reder simple sphere cast

    Vector3 CastRay(
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

    void WriteSimpleSphereCastToBuffer(
        List<Vector3>& framebuffer,
        int width,
        int height,
        float fov,
        const Sphere& sphere)
    {
        for (size_t j = 0; j < height; j++)
        {
            for (size_t i = 0; i < width; i++)
            {
                float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
                
                float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
                
                Vector3 dir = glm::normalize(glm::vec3(x, y, -1));
                
                framebuffer[i + j * width] = CastRay(
                    Vector3(0, 0, 0),
                    dir,
                    sphere);
            }
        }
    }

    void RenderSimpleSphereCast(const Sphere& sphere) 
    {
        const int width = 1024;
        const int height = 768;
        
        const float fov = glm::pi<float>() / 2.f; //1.05; // 60 degrees field of view in radians
        
        List<Vector3> framebuffer(width * height);
        
        WriteSimpleSphereCastToBuffer(framebuffer, width, height, fov, sphere);

        SaveBufferToImage(framebuffer, width, height);
    }
    
    #pragma endregion
    
    #pragma region Render sphere cast with materials
    
    bool CastRay(
        const Vector3& origin,
        const Vector3& direction,
        const List<SphereObject>& spheres,
        Vector3& hitPosition,
        Vector3& normal,
        Material& material)
    {
        float distanceToSpheres = std::numeric_limits<float>::max();
        
        for (size_t i=0; i < spheres.size(); i++)
        {
            float currentDistance;
            
            if (spheres[i].GetSphere().RayIntersect(origin, direction, currentDistance) 
                && currentDistance < distanceToSpheres)
            {
                distanceToSpheres = currentDistance;
                
                hitPosition = origin + direction * currentDistance;
                
                normal = glm::normalize(hitPosition - spheres[i].GetSphere().GetCenter());
                
                material = spheres[i].GetMaterial();
            }
        }
        
        return distanceToSpheres < 1000;
    }
    
    Vector3 CastRay(
        const Vector3 &origin,
        const Vector3 &direction,
        const List<SphereObject> &spheres)
    {
        Vector3 hitPosition, normal;
        
        Material material;

        if (!CastRay(origin, direction, spheres, hitPosition, normal, material))
        {
            return Vector3(0.2, 0.7, 0.8); // background color
        }
        
        return material.GetDiffuseColor();
    }
    
    void WriteSphereCastWithMaterialsToBuffer(
        List<Vector3>& framebuffer,
        int width,
        int height,
        float fov,
        const List<SphereObject>& spheres)
    {
        for (size_t j = 0; j < height; j++)
        {
            for (size_t i = 0; i < width; i++)
            {
                float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
                
                float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
                
                Vector3 dir = glm::normalize(glm::vec3(x, y, -1));
                
                framebuffer[i + j * width] = CastRay(
                    Vector3(0, 0, 0),
                    dir,
                    spheres);
            }
        }
    }
    
    void RenderSphereCastWithMaterials(const List<SphereObject>& spheres)
    {
        const int width = 1024;
        const int height = 768;
        
        const float fov = glm::pi<float>() / 2.f; //1.05; // 60 degrees field of view in radians
        
        List<Vector3> framebuffer(width * height);
        
        WriteSphereCastWithMaterialsToBuffer(framebuffer, width, height, fov, spheres);

        SaveBufferToImage(framebuffer, width, height);
    }
    
    #pragma endregion
}