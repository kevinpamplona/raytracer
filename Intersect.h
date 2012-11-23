#include "variables.h"


class Intersect
{
public:
    Intersect();
    virtual ~Intersect();
    
    static Hit hit(ray r, int m, int n);
    static float getDepth(ray r, float t, glm::vec3 p);
    static int getNearestObject(hitShape s, hitShape t);
};


