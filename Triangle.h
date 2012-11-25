#include "variables.h"

class Triangle
{
public:
    Triangle();
    virtual ~Triangle();
    
    static hitShape intersect (tri t, ray r);
};