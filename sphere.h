#include "variables.h"

class Sphere
{
public:
    Sphere();
    virtual ~Sphere();
    
    static hitShape intersect (sphere s, ray r);
    
};