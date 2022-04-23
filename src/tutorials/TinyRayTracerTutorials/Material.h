#include <glm/vec3.hpp>

using Color = glm::vec3;

namespace TinyRayTracerTutorials
{
    struct Material 
    {
        private:
            Color diffuseColor;
        
        public:
            Material(const Color& color);
            
            Material();
            
            //Here are some takeaways I did working on this little tiny itty bitty part
            
            //1. As I said in Sphere.h, C++ plebs have no C# properties. Fuck it, will do them manually
            
            //2. C++ allows methods to have names equal to return value types just like C# does. Good
            
            //3. C++ allows arguments to have names equal to local variables just like C# does. Also, it allows for
            //constructions like Constructor(fancytype foo) : foo(foo) {...} where you declare local variable with the argument
            //of the same name after the constructor signature without this->... . Sweet
            
            //4. C++ has some kind of deranged form of bipolar disorder. For instance, as in Sphere.H, you can have an alias to type used as:
            //- a variable type
            //- an argument type in methods and constructors
            //- a return type of a method
            //And it works for both .h file and .cpp file. Cool. But once you decide to name any method the same as the alias (for instance,
            //name both alias and getter method 'Color') the compiler rolls with it for the .h file but goes apeshit in .cpp file,
            //stating that is has no idea what this 'Color' type is, vomiting unrelated errors on all occurences of 'Color' used as a type name
            //and offering you to change it to '::Color' instead (which obviously looks ugly)
            //So discretion is advised when using aliases together with features that C++ is obviously missing from its better counterpart (C#)
            
            //5. The bipolar disorder I mentioned before is strong with this one. As tested separately in SphereObject.h, and confirmed here
            //(https://stackoverflow.com/questions/467815/class-method-and-variable-with-same-name-compile-error-in-c-not-in-java),
            //C++ is OK with methods having the same name as return value types... only if you don't use said types as constructor arguments.
            //Once again, it rolls with it in .h files but starts freaking out in .cpp files. This time however it still allows for, say,
            //'Sphere SphereObject::Sphere'. The easiest path you can take to ensure thiis psycho leaves you alone with the multiverse
            //of its stupid syntax is to name getters and setters explicitly GetBlaBla SetBlaBla
            
            Color GetDiffuseColor();
    };
}