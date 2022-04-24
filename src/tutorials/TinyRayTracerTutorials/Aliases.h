#include <vector>
#include <glm/vec3.hpp>

//This construct is called 'Include Guard'. It exists because C++ compilers exist. Here's a good article on the subject:
//https://www.jacksondunstan.com/articles/5553

#ifndef ALIASES
#define ALIASES

//See this? This is how you name your classes/structs properly, just like the good old C# MSDN codestyle tells you to
//- PascalCase for names
//- No stupid abbreviations (NSDMI, PIMPL etc.)
//- No stupid short names. Vector is a vector, not vec
//- No long cascades of foo::bar::foo::bar
//- No stupid underscores
//- No stupid starting underscores
//- No stupid trailing underscores
//- No stupid multiple underscores
//- No stupid letter-and-underscore prefixes

//In C++ you specify a generic with a template<...> prefix (rather than postfix like in C#) before the class/struct/method 
//declaratioin/definition. Also when using aliases you don't have to do Stuff<T> = someOtherStuff<T> - the template<> prefix has
//already done it for you. The wild thing is that this, as well as lvalue references, has made its way into C++ only in C++11.

template<typename TValue>
using List = std::vector<TValue>;

using Color = glm::vec3;
using Vector3 = glm::vec3;
    
#endif