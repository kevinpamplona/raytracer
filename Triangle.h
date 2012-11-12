#include "variables.h"

class Triangle
{
public:
    Triangle();
    virtual ~Triangle();
    
    static bool intersect (tri t, ray r);

};