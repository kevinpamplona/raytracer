#include "variables.h"

class Sphere
{
public:
    Sphere();
    virtual ~Sphere();
    
    static hitShape intersect (sphere s, ray r);
    static glm::vec3 getNormal (sphere s, glm::vec3 isect);
    
};