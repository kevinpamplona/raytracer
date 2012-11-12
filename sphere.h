#include "variables.h"

class Sphere
{
public:
    Sphere();
    virtual ~Sphere();
    
    static bool intersect (sphere s, ray r);
    
};