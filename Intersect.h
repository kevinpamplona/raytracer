#include "variables.h"


class Intersect
{
public:
    Intersect();
    virtual ~Intersect();
    
    static bool hit(ray r);
};


